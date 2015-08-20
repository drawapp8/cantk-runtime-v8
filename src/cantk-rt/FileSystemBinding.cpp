#include "FileSystem.h"

#include "FileSystemBinding.h"

NAN_METHOD(newFileSystem) {
	NanScope();

	FileSystem* obj = new FileSystem();
	obj->Wrap(args.This());

	NanReturnValue(args.This());
}

typedef struct _ReadCtx {
	string type;
	NanCallback* onDone;
}ReadCtx;

static void onReadResult(void* ctx, char* content, int length) {
	NanScope();

	ReadCtx* readCtx = (ReadCtx*)ctx;
	uint8_t* buff = (uint8_t*)content;
	bool userDefinedType = readCtx->type.find("x-user-defined") >= 0;

	Handle<String> str = userDefinedType ? String::NewFromOneByte(Isolate::GetCurrent(),buff,String::kNormalString,length):NanNew<String>(buff);

	if(readCtx->onDone) {
		Handle<Value> argv[1] = {str};
		readCtx->onDone->Call(1, argv);
		delete readCtx->onDone;
	}

	delete readCtx;
}

NAN_METHOD(FileSystemReadAsText) {
	NanScope();

	string name;
	string type;
	NanCallback* onDone = NULL;
	int argsLength = args.Length();
	FileSystem* obj = ObjectWrap::Unwrap<FileSystem>(args.This());

	if(argsLength > 0) {
		v8::String::Utf8Value src(args[0]);
		const char* p = *src;
		if(strncmp(p, "file://", 7) == 0) {
			p += 7;
		}	
		name = p;
	}
	
	if(argsLength > 1) {
		v8::String::Utf8Value mimeType(args[1]);
		type = *mimeType;	
	}
	
	if(argsLength > 2) {
		onDone = new NanCallback(args[2].As<Function>());
	}

	if(!onDone) {
		//sync read
		int length = 0;
		uint8_t* buff = NULL;
		bool ret = FileSystem::readFileSync(name.c_str(), (char**)&buff, &length);

		if(ret) {
			if(type.find("x-user-defined") >= 0) {
				Handle<String> str = String::NewFromOneByte(Isolate::GetCurrent(),buff,String::kNormalString,length);
				NanReturnValue(str);
			}
			else {
				Handle<String> str = NanNew<String>(buff);
				NanReturnValue(str);
			}
			delete buff;
		}
		else {
			NanReturnNull();
		}
	}
	else {
		//async read
		ReadCtx* ctx = new ReadCtx();

		ctx->type = type;
		ctx->onDone = onDone;
		FileSystem::readFile(name.c_str(), onReadResult, ctx);
	}

	return;
}


NAN_GETTER(FileSystemGetCwd) {
	NanScope();
	FileSystem* obj = ObjectWrap::Unwrap<FileSystem>(args.This());
	NanReturnValue(NanNew<String>(obj->getCwd()));
}

NAN_SETTER(FileSystemSetCwd) {
	NanScope();
	FileSystem* obj = ObjectWrap::Unwrap<FileSystem>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setCwd(*nativeValue);
	}else{
		printf("invalid data type for FileSystem.cwd\n");
	}
}


static Persistent<FunctionTemplate> constructor;
void FileSystemInitBinding(Handle<Object> target) {
	NanScope();
	Local<FunctionTemplate> ctor = NanNew<FunctionTemplate>(newFileSystem);
	NanAssignPersistent(constructor, ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(NanNew("FileSystem"));
	Local<ObjectTemplate> proto = ctor->PrototypeTemplate();
	
	proto->SetAccessor(NanNew("cwd"), FileSystemGetCwd, FileSystemSetCwd);

	NAN_SET_PROTOTYPE_METHOD(ctor, "readAsText", FileSystemReadAsText);


	target->Set(NanNew("FileSystem"), ctor->GetFunction());

}
