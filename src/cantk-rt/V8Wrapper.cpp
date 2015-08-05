#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <errno.h>
#include "Native.h"
#include "V8Wrapper.h"
#include "CanvasRenderingContext2d.h"

int getIntOption(int argc, char** argv, const char* prefix, int defval) {
	int len = strlen(prefix);
	for(int i = 0; i < argc; i++) {
		const char* iter = argv[i];
		if(strncmp(iter, prefix, len) == 0) {
			int v = atoi(iter + len);
			return v;
		}
	}

	return defval;
}

const char* getStrOption(int argc, char** argv, const char* prefix, const char* defval) {
	int len = strlen(prefix);
	for(int i = 0; i < argc; i++) {
		const char* iter = argv[i];
		if(strncmp(iter, prefix, len) == 0) {
			return (iter + len);
		}
	}

	return defval;
}


class SimpleArrayBufferAllocator : public ArrayBuffer::Allocator {
 public:
  virtual void* Allocate(size_t length) {
    void* data = AllocateUninitialized(length);
    return data == NULL ? data : memset(data, 0, length);
  }
  virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
  virtual void Free(void* data, size_t) { free(data); }
};

template <class TypeName>
inline Local<TypeName> StrongPersistentToLocal(
    const Persistent<TypeName>& persistent) {
  return *reinterpret_cast<Local<TypeName>*>(
      const_cast<Persistent<TypeName>*>(&persistent));
}

template <class TypeName>
inline Local<TypeName> WeakPersistentToLocal(
    Isolate* isolate,
    const Persistent<TypeName>& persistent) {
  return Local<TypeName>::New(isolate, persistent);
}

template <class TypeName>
inline Local<TypeName> PersistentToLocal(
    Isolate* isolate,
    const Persistent<TypeName>& persistent) {
  if (persistent.IsWeak()) {
    return WeakPersistentToLocal(isolate, persistent);
  } else {
    return StrongPersistentToLocal(persistent);
  }
}

///////////////////////////////////////////////////////
// Extracts a C string from a V8 Utf8Value.
static const char* ToCString(const String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

static void ReportException(Isolate* isolate, TryCatch* try_catch) {
  HandleScope handle_scope(isolate);
  String::Utf8Value exception(try_catch->Exception());
  const char* exception_string = ToCString(exception);
  Handle<Message> message = try_catch->Message();
  if (message.IsEmpty()) {
    // V8 didn't provide any extra information about this error; just
    // print the exception.
    LOGE("%s\n", exception_string);
  } else {
    // Print (filename):(line number): (message).
    String::Utf8Value filename(message->GetScriptOrigin().ResourceName());
    const char* filename_string = ToCString(filename);
    int linenum = message->GetLineNumber();
    LOGE("%s:%i: %s\n", filename_string, linenum, exception_string);
    // Print line of source code.
    String::Utf8Value sourceline(message->GetSourceLine());
    const char* sourceline_string = ToCString(sourceline);
    LOGE("%s\n", sourceline_string);
    // Print wavy underline (GetUnderline is deprecated).
    int start = message->GetStartColumn();
    for (int i = 0; i < start; i++) {
      LOGE(" ");
    }
    int end = message->GetEndColumn();
    for (int i = start; i < end; i++) {
      LOGE("^");
    }
    LOGE("\n");
    String::Utf8Value stack_trace(try_catch->StackTrace());
    if (stack_trace.length() > 0) {
      const char* stack_trace_string = ToCString(stack_trace);
      LOGE("%s\n", stack_trace_string);
    }
  }
}

static Handle<String> ReadFile(Isolate* isolate, const char* name) {
  FILE* file = fopen(name, "rb");
  if (file == NULL) {
	LOGI("open file failed: %s %d\n", name, errno);
  	return Handle<String>();
  }

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);

  char* chars = new char[size + 1];
  chars[size] = '\0';
  for (int i = 0; i < size;) {
    int read = static_cast<int>(fread(&chars[i], 1, size - i, file));
    i += read;
  }
  fclose(file);
  Handle<String> result =
      String::NewFromUtf8(isolate, chars, String::kNormalString, size);
  delete[] chars;
  return result;
}

static bool ExecuteString(Isolate* isolate, Handle<String> source,
				Handle<Value> name, bool print_result,  bool report_exceptions) {
  HandleScope handle_scope(isolate);
  TryCatch try_catch;
  ScriptOrigin origin(name);
  Handle<Script> script = Script::Compile(source, &origin);
  if (script.IsEmpty()) {
    // Print errors that happened during compilation.
    if (report_exceptions)
      ReportException(isolate, &try_catch);
    return false;
  } else {
    Handle<Value> result = script->Run();
    if (result.IsEmpty()) {
      assert(try_catch.HasCaught());
      // Print errors that happened during execution.
      if (report_exceptions)
        ReportException(isolate, &try_catch);
      return false;
    } else {
      assert(!try_catch.HasCaught());
      if (print_result && !result->IsUndefined()) {
        // If all went well and the result wasn't undefined then print
        // the returned value.
        String::Utf8Value str(result);
        const char* cstr = ToCString(str);
        LOGI("%s\n", cstr);
      }
      return true;
    }
  }
}


void Print(const FunctionCallbackInfo<Value>& args) {
  bool first = true;
  for (int i = 0; i < args.Length(); i++) {
    HandleScope handle_scope(args.GetIsolate());
    if (first) {
      first = false;
    } else {
      CONSOLE_LOG(" ");
    }
    String::Utf8Value str(args[i]);
    const char* cstr = ToCString(str);
    CONSOLE_LOG("%s", cstr);
  }
  CONSOLE_LOG("\n");
}

void Load(const v8::FunctionCallbackInfo<v8::Value>& args) {
  for (int i = 0; i < args.Length(); i++) {
    v8::HandleScope handle_scope(args.GetIsolate());
    v8::String::Utf8Value file(args[i]);
    if (*file == NULL) {
      args.GetIsolate()->ThrowException(
          v8::String::NewFromUtf8(args.GetIsolate(), "Error loading file"));
      return;
    }
    v8::Handle<v8::String> source = ReadFile(args.GetIsolate(), *file);
    if (source.IsEmpty()) {
      args.GetIsolate()->ThrowException(
           v8::String::NewFromUtf8(args.GetIsolate(), "Error loading file"));
      return;
    }
    if (!ExecuteString(args.GetIsolate(),
                       source,
                       v8::String::NewFromUtf8(args.GetIsolate(), *file),
                       true,
                       true)) {
      args.GetIsolate()->ThrowException(
          v8::String::NewFromUtf8(args.GetIsolate(), "Error executing file"));
      return;
    }
  }
}

Handle<Context> CreateDefaultContext(Isolate* isolate) {
  // Create a template for the global object.
  Handle<ObjectTemplate> global = ObjectTemplate::New(isolate);
  // Bind the global 'print' function to the C++ Print callback.
  global->Set(String::NewFromUtf8(isolate, "print"), FunctionTemplate::New(isolate, Print));
  global->Set(String::NewFromUtf8(isolate, "require"), FunctionTemplate::New(isolate, Load));

  Handle<Context> context = Context::New(isolate, NULL, global);
  
  return context;
}

int RunMain(Isolate* isolate, int argc, char* argv[]) {
	char cwd[1024] = {0};
	char fullFileName[1024] = {0};
	const char* str = getStrOption(argc, argv, "--startup=", "assets/scripts/startup.js");

	LOGI("Run: %s\n", str);

	if(str[0] != '/') {
		getcwd(cwd, sizeof(cwd));
		snprintf(fullFileName, sizeof(fullFileName)-1, "%s/%s", cwd, str);
	}
	else {
		strncpy(fullFileName, str, sizeof(fullFileName)-1);
	}

	const char* last = strrchr(fullFileName, '/');
	strncpy(cwd, fullFileName, last-fullFileName);
	chdir(cwd);

	const char* fileName = last+1;
	Handle<String> source = ReadFile(isolate, fullFileName);
	int result = !ExecuteString(isolate, source, NanNew<String>(fileName), false, true);

	return result;
}


///////////////////////////////////////////
V8Wrapper::V8Wrapper() {

}

V8Wrapper::~V8Wrapper() {
}
	
void V8Wrapper::init(int argc, char* argv[]) {
	LOGI("V8Wrapper::init:%d\n", argc);
	V8::InitializeICU();
	Platform* platform = platform::CreateDefaultPlatform();
	V8::InitializePlatform(platform);
	V8::Initialize();
	V8::SetFlagsFromCommandLine(&argc, argv, true);
	SimpleArrayBufferAllocator array_buffer_allocator;
	V8::SetArrayBufferAllocator(&array_buffer_allocator);
	Isolate* isolate = Isolate::New();
	
	isolate->Enter();
    HandleScope handle_scope(isolate);
	V8Wrapper::sContext = CreateDefaultContext(isolate);
	V8Wrapper::sContext->Enter();

    if (V8Wrapper::sContext.IsEmpty()) {
      LOGE("Error creating context\n");
      return;
    }

	nativeInitBinding(V8Wrapper::sContext->Global());
	CanvasRenderingContext2d::init();

    RunMain(isolate, argc, argv);
	Handle<Value> tickVal = V8Wrapper::sContext->Global()->Get(NanNew("tick"));
	if (!tickVal->IsFunction()) {
		LOGI("Error: Script does not declare 'tick' global function.\n");
		return;
	}
	Handle<Function> tickFunc = Handle<Function>::Cast(tickVal);
	NanAssignPersistent(V8Wrapper::sTickFunc, tickFunc);
    
	Handle<Value> dispatchEventVal = V8Wrapper::sContext->Global()->Get(NanNew("dispatchEvent"));
	if (!dispatchEventVal->IsFunction()) {
		LOGI("Error: Script does not declare 'dispatchEvent' global function.\n");
		return;
	}
	Handle<Function> dispatchEventFunc = Handle<Function>::Cast(dispatchEventVal);
	NanAssignPersistent(V8Wrapper::sDispatchEventFunc, dispatchEventFunc);

	V8Wrapper::sPlatform = platform;
	V8Wrapper::sIsolate = isolate;
	LOGI("V8Wrapper::init done\n");
}

void V8Wrapper::deinit() {
	V8::Dispose();
	V8::ShutdownPlatform();
	delete V8Wrapper::sPlatform;
	V8Wrapper::sPlatform = NULL;
	CanvasRenderingContext2d::deinit();
}

void V8Wrapper::resize(int w, int h) {
	CanvasRenderingContext2d::resize(w, h);
}

void V8Wrapper::tick(double t, double dt) {
	NanScope();
	Isolate* isolate = V8Wrapper::sIsolate;
    Isolate::Scope isolate_scope(isolate);
	Handle<Function> tickFunc = NanNew(V8Wrapper::sTickFunc);

	CanvasRenderingContext2d::beginPaint();

	TryCatch try_catch;
	Handle<Value> _argv[2];
	_argv[0] = Number::New(isolate, t);
	_argv[1] = Number::New(isolate, dt);

	Handle<Value> result = tickFunc->Call(isolate->GetCurrentContext()->Global(), 2, _argv);
	
	if (try_catch.HasCaught()) {
		ReportException(isolate, &try_catch);
		return;
	}
	CanvasRenderingContext2d::endPaint();
}
	
void V8Wrapper::dispatchEvent(Handle<Object> event) {
	Handle<Value> _argv[1] = {event};
	Handle<Function> func = NanNew(V8Wrapper::sDispatchEventFunc);

	func->Call(Isolate::GetCurrent()->GetCurrentContext()->Global(), 1, _argv);
}

void V8Wrapper::dispatchPointerEvent(int action, int button, int x, int y) {
	NanScope();
	Handle<Object> obj = NanNew<Object>();
	
	if(action == 1) {
		obj->Set(NanNew("name"), NanNew("pointerdown"));
	}
	else if(action == 0) {
		obj->Set(NanNew("name"), NanNew("pointerup"));
	}
	else if(action == 3) {
		obj->Set(NanNew("name"), NanNew("pointermove"));
	}

	obj->Set(NanNew("action"), NanNew<Number>(action));
	obj->Set(NanNew("button"), NanNew<Number>(button));
	obj->Set(NanNew("x"), NanNew<Number>(x));
	obj->Set(NanNew("y"), NanNew<Number>(y));

	V8Wrapper::dispatchEvent(obj);
}

void V8Wrapper::dispatchKeyEvent(int action, int code, int mods, int scancode) {
	NanScope();
	Handle<Object> obj = NanNew<Object>();

	if(action == 1) {
		obj->Set(NanNew("name"), NanNew("keydown"));
	}
	else if(action == 0) {
		obj->Set(NanNew("name"), NanNew("keyup"));
	}
	else if(action == 2) {
		obj->Set(NanNew("name"), NanNew("keyrepeat"));
	}
	else {
		obj->Set(NanNew("name"), NanNew("key"));
	}

	obj->Set(NanNew("action"), NanNew<Number>(action));
	obj->Set(NanNew("code"), NanNew<Number>(code));
	obj->Set(NanNew("mods"), NanNew<Number>(mods));
	obj->Set(NanNew("scancode"), NanNew<Number>(scancode));

	V8Wrapper::dispatchEvent(obj);
}

Isolate* V8Wrapper::sIsolate = NULL;
Platform* V8Wrapper::sPlatform = NULL;
Persistent<Function> V8Wrapper::sTickFunc;
Handle<Context> V8Wrapper::sContext;
Persistent<Function> V8Wrapper::sDispatchEventFunc;


