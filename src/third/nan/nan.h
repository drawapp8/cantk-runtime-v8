/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors:
 *   - Rod Vagg <https://github.com/rvagg>
 *   - Benjamin Byholm <https://github.com/kkoopa>
 *   - Trevor Norris <https://github.com/trevnorris>
 *   - Nathan Rajlich <https://github.com/TooTallNate>
 *   - Brett Lawson <https://github.com/brett19>
 *   - Ben Noordhuis <https://github.com/bnoordhuis>
 *   - David Siegel <https://github.com/agnat>
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 *
 * Version 1.8.4: current Node 12: 0.12.2, Node 10: 0.10.38, io.js: 1.8.1
 *
 * See https://github.com/nodejs/nan for the latest update to this file
 **********************************************************************************/

#ifndef NAN_H_
#define NAN_H_

#include <cstring>
#include <climits>
#include <cstdlib>

# define NAN_EXTERN

#if defined(_MSC_VER)
# pragma warning( push )
# pragma warning( disable : 4530 )
# include <string>
# pragma warning( pop )
#else
# include <string>
#endif

#if defined(__GNUC__) && !(defined(DEBUG) && DEBUG)
# define NAN_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER) && !(defined(DEBUG) && DEBUG)
# define NAN_INLINE __forceinline
#else
# define NAN_INLINE inline
#endif

#if defined(__GNUC__) && \
    !(defined(V8_DISABLE_DEPRECATIONS) && V8_DISABLE_DEPRECATIONS)
# define NAN_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER) && \
    !(defined(V8_DISABLE_DEPRECATIONS) && V8_DISABLE_DEPRECATIONS)
# define NAN_DEPRECATED __declspec(deprecated)
#else
# define NAN_DEPRECATED
#endif

#if __cplusplus >= 201103L
# define NAN_DISALLOW_ASSIGN(CLASS) void operator=(const CLASS&) = delete;
# define NAN_DISALLOW_COPY(CLASS) CLASS(const CLASS&) = delete;
# define NAN_DISALLOW_MOVE(CLASS)                                              \
    CLASS(CLASS&&) = delete;  /* NOLINT(build/c++11) */                        \
    void operator=(CLASS&&) = delete;
#else
# define NAN_DISALLOW_ASSIGN(CLASS) void operator=(const CLASS&);
# define NAN_DISALLOW_COPY(CLASS) CLASS(const CLASS&);
# define NAN_DISALLOW_MOVE(CLASS)
#endif

#define NAN_DISALLOW_ASSIGN_COPY(CLASS)                                        \
    NAN_DISALLOW_ASSIGN(CLASS)                                                 \
    NAN_DISALLOW_COPY(CLASS)

#define NAN_DISALLOW_ASSIGN_MOVE(CLASS)                                        \
    NAN_DISALLOW_ASSIGN(CLASS)                                                 \
    NAN_DISALLOW_MOVE(CLASS)

#define NAN_DISALLOW_COPY_MOVE(CLASS)                                          \
    NAN_DISALLOW_COPY(CLASS)                                                   \
    NAN_DISALLOW_MOVE(CLASS)

#define NAN_DISALLOW_ASSIGN_COPY_MOVE(CLASS)                                   \
    NAN_DISALLOW_ASSIGN(CLASS)                                                 \
    NAN_DISALLOW_COPY(CLASS)                                                   \
    NAN_DISALLOW_MOVE(CLASS)

typedef v8::FunctionCallback   NanFunctionCallback;
typedef v8::UnboundScript      NanUnboundScript;
typedef v8::Script             NanBoundScript;
typedef v8::String::ExternalOneByteStringResource
    NanExternalOneByteStringResource;

#include "nan_new.h"  // NOLINT(build/include)
#include "object_wrap.h"

// some generic helpers

namespace Nan { namespace imp {
template<typename T> NAN_INLINE bool NanSetPointerSafe(
    T *var
  , T val
) {
  if (var) {
    *var = val;
    return true;
  } else {
    return false;
  }
}

template<typename T> NAN_INLINE T NanGetPointerSafe(
    T *var
  , T fallback = reinterpret_cast<T>(0)
) {
  if (var) {
    return *var;
  } else {
    return fallback;
  }
}

NAN_INLINE bool NanBooleanOptionValue(
    v8::Local<v8::Object> optionsObj
  , v8::Handle<v8::String> opt, bool def
) {
  if (def) {
    return optionsObj.IsEmpty()
      || !optionsObj->Has(opt)
      || optionsObj->Get(opt)->BooleanValue();
  } else {
    return !optionsObj.IsEmpty()
      && optionsObj->Has(opt)
      && optionsObj->Get(opt)->BooleanValue();
  }
}

}  // end of namespace imp
}  // end of namespace Nan

template<typename T> v8::Local<T> NanNew(v8::Handle<T>);

namespace Nan { namespace imp {
  template<typename T>
  NAN_INLINE v8::Persistent<T> &NanEnsureHandleOrPersistent(
      v8::Persistent<T> &val) {  // NOLINT(runtime/references)
    return val;
  }

  template<typename T>
  NAN_INLINE
  v8::Handle<T> NanEnsureHandleOrPersistent(const v8::Handle<T> &val) {
    return val;
  }

  template<typename T>
  NAN_INLINE v8::Local<T> NanEnsureHandleOrPersistent(const v8::Local<T> &val) {
    return val;
  }

  template<typename T>
  NAN_INLINE v8::Local<v8::Value> NanEnsureHandleOrPersistent(const T &val) {
    return NanNew(val);
  }

  template<typename T>
  NAN_INLINE v8::Local<T> NanEnsureLocal(const v8::Local<T> &val) {
    return val;
  }

  template<typename T>
  NAN_INLINE v8::Local<T> NanEnsureLocal(const v8::Persistent<T> &val) {
    return NanNew(val);
  }

  template<typename T>
  NAN_INLINE v8::Local<T> NanEnsureLocal(const v8::Handle<T> &val) {
    return NanNew(val);
  }

  template<typename T>
  NAN_INLINE v8::Local<v8::Value> NanEnsureLocal(const T &val) {
    return NanNew(val);
  }
}  // end of namespace imp
}  // end of namespace Nan

  NAN_INLINE
  void NanSetCounterFunction(v8::CounterLookupCallback cb) {
    v8::Isolate::GetCurrent()->SetCounterFunction(cb);
  }

  NAN_INLINE
  void NanSetCreateHistogramFunction(v8::CreateHistogramCallback cb) {
    v8::Isolate::GetCurrent()->SetCreateHistogramFunction(cb);
  }

  NAN_INLINE
  void NanSetAddHistogramSampleFunction(v8::AddHistogramSampleCallback cb) {
    v8::Isolate::GetCurrent()->SetAddHistogramSampleFunction(cb);
  }

  NAN_INLINE bool NanIdleNotification(int idle_time_in_ms) {
    return v8::Isolate::GetCurrent()->IdleNotification(idle_time_in_ms);
  }

  NAN_INLINE void NanLowMemoryNotification() {
    v8::Isolate::GetCurrent()->LowMemoryNotification();
  }

  NAN_INLINE void NanContextDisposedNotification() {
    v8::Isolate::GetCurrent()->ContextDisposedNotification();
  }

# define _NAN_METHOD_ARGS_TYPE const v8::FunctionCallbackInfo<v8::Value>&
# define _NAN_METHOD_ARGS _NAN_METHOD_ARGS_TYPE args
# define _NAN_METHOD_RETURN_TYPE void

# define _NAN_GETTER_ARGS_TYPE const v8::PropertyCallbackInfo<v8::Value>&
# define _NAN_GETTER_ARGS _NAN_GETTER_ARGS_TYPE args
# define _NAN_GETTER_RETURN_TYPE void

# define _NAN_SETTER_ARGS_TYPE const v8::PropertyCallbackInfo<void>&
# define _NAN_SETTER_ARGS _NAN_SETTER_ARGS_TYPE args
# define _NAN_SETTER_RETURN_TYPE void

# define _NAN_PROPERTY_GETTER_ARGS_TYPE                                        \
    const v8::PropertyCallbackInfo<v8::Value>&
# define _NAN_PROPERTY_GETTER_ARGS _NAN_PROPERTY_GETTER_ARGS_TYPE args
# define _NAN_PROPERTY_GETTER_RETURN_TYPE void

# define _NAN_PROPERTY_SETTER_ARGS_TYPE                                        \
    const v8::PropertyCallbackInfo<v8::Value>&
# define _NAN_PROPERTY_SETTER_ARGS _NAN_PROPERTY_SETTER_ARGS_TYPE args
# define _NAN_PROPERTY_SETTER_RETURN_TYPE void

# define _NAN_PROPERTY_ENUMERATOR_ARGS_TYPE                                    \
    const v8::PropertyCallbackInfo<v8::Array>&
# define _NAN_PROPERTY_ENUMERATOR_ARGS _NAN_PROPERTY_ENUMERATOR_ARGS_TYPE args
# define _NAN_PROPERTY_ENUMERATOR_RETURN_TYPE void

# define _NAN_PROPERTY_DELETER_ARGS_TYPE                                       \
    const v8::PropertyCallbackInfo<v8::Boolean>&
# define _NAN_PROPERTY_DELETER_ARGS                                            \
    _NAN_PROPERTY_DELETER_ARGS_TYPE args
# define _NAN_PROPERTY_DELETER_RETURN_TYPE void

# define _NAN_PROPERTY_QUERY_ARGS_TYPE                                         \
    const v8::PropertyCallbackInfo<v8::Integer>&
# define _NAN_PROPERTY_QUERY_ARGS _NAN_PROPERTY_QUERY_ARGS_TYPE args
# define _NAN_PROPERTY_QUERY_RETURN_TYPE void

# define _NAN_INDEX_GETTER_ARGS_TYPE                                           \
    const v8::PropertyCallbackInfo<v8::Value>&
# define _NAN_INDEX_GETTER_ARGS _NAN_INDEX_GETTER_ARGS_TYPE args
# define _NAN_INDEX_GETTER_RETURN_TYPE void

# define _NAN_INDEX_SETTER_ARGS_TYPE                                           \
    const v8::PropertyCallbackInfo<v8::Value>&
# define _NAN_INDEX_SETTER_ARGS _NAN_INDEX_SETTER_ARGS_TYPE args
# define _NAN_INDEX_SETTER_RETURN_TYPE void

# define _NAN_INDEX_ENUMERATOR_ARGS_TYPE                                       \
    const v8::PropertyCallbackInfo<v8::Array>&
# define _NAN_INDEX_ENUMERATOR_ARGS _NAN_INDEX_ENUMERATOR_ARGS_TYPE args
# define _NAN_INDEX_ENUMERATOR_RETURN_TYPE void

# define _NAN_INDEX_DELETER_ARGS_TYPE                                          \
    const v8::PropertyCallbackInfo<v8::Boolean>&
# define _NAN_INDEX_DELETER_ARGS _NAN_INDEX_DELETER_ARGS_TYPE args
# define _NAN_INDEX_DELETER_RETURN_TYPE void

# define _NAN_INDEX_QUERY_ARGS_TYPE                                            \
    const v8::PropertyCallbackInfo<v8::Integer>&
# define _NAN_INDEX_QUERY_ARGS _NAN_INDEX_QUERY_ARGS_TYPE args
# define _NAN_INDEX_QUERY_RETURN_TYPE void

# define NanScope() v8::HandleScope scope(v8::Isolate::GetCurrent())
# define NanEscapableScope()                                                   \
  v8::EscapableHandleScope scope(v8::Isolate::GetCurrent())

# define NanEscapeScope(val) scope.Escape(Nan::imp::NanEnsureLocal(val))
# define NanLocker() v8::Locker locker(v8::Isolate::GetCurrent())
# define NanUnlocker() v8::Unlocker unlocker(v8::Isolate::GetCurrent())
# define NanReturnValue(value)                                                 \
return args.GetReturnValue().Set(Nan::imp::NanEnsureHandleOrPersistent(value))
# define NanReturnUndefined() return
# define NanReturnHolder() NanReturnValue(args.Holder())
# define NanReturnThis() NanReturnValue(args.This())
# define NanReturnNull() return args.GetReturnValue().SetNull()
# define NanReturnEmptyString() return args.GetReturnValue().SetEmptyString()

  NAN_INLINE
  v8::Local<v8::Object> NanObjectWrapHandle(const ObjectWrap *obj) {
    return const_cast<ObjectWrap*>(obj)->handle();
  }

  NAN_INLINE v8::Local<v8::Primitive> NanUndefined() {
    NanEscapableScope();
    return NanEscapeScope(NanNew(v8::Undefined(v8::Isolate::GetCurrent())));
  }

  NAN_INLINE v8::Local<v8::Primitive> NanNull() {
    NanEscapableScope();
    return NanEscapeScope(NanNew(v8::Null(v8::Isolate::GetCurrent())));
  }

  NAN_INLINE v8::Local<v8::Boolean> NanTrue() {
    NanEscapableScope();
    return NanEscapeScope(NanNew(v8::True(v8::Isolate::GetCurrent())));
  }

  NAN_INLINE v8::Local<v8::Boolean> NanFalse() {
    NanEscapableScope();
    return NanEscapeScope(NanNew(v8::False(v8::Isolate::GetCurrent())));
  }

  NAN_INLINE int NanAdjustExternalMemory(int bc) {
    return static_cast<int>(
        v8::Isolate::GetCurrent()->AdjustAmountOfExternalAllocatedMemory(bc));
  }

  NAN_INLINE void NanSetTemplate(
      v8::Handle<v8::Template> templ
    , const char *name
    , v8::Handle<v8::Data> value) {
    templ->Set(v8::Isolate::GetCurrent(), name, value);
  }

  NAN_INLINE void NanSetTemplate(
      v8::Handle<v8::Template> templ
    , v8::Handle<v8::String> name
    , v8::Handle<v8::Data> value
    , v8::PropertyAttribute attributes) {
    templ->Set(name, value, attributes);
  }

  NAN_INLINE v8::Local<v8::Context> NanGetCurrentContext() {
    return v8::Isolate::GetCurrent()->GetCurrentContext();
  }

  NAN_INLINE void* NanGetInternalFieldPointer(
      v8::Handle<v8::Object> object
    , int index) {
    return object->GetAlignedPointerFromInternalField(index);
  }

  NAN_INLINE void NanSetInternalFieldPointer(
      v8::Handle<v8::Object> object
    , int index
    , void* value) {
    object->SetAlignedPointerInInternalField(index, value);
  }

# define NAN_GC_CALLBACK(name)                                                 \
    void name(v8::Isolate *isolate, v8::GCType type, v8::GCCallbackFlags flags)

  NAN_INLINE void NanAddGCEpilogueCallback(
      v8::Isolate::GCEpilogueCallback callback
    , v8::GCType gc_type_filter = v8::kGCTypeAll) {
    v8::Isolate::GetCurrent()->AddGCEpilogueCallback(callback, gc_type_filter);
  }

  NAN_INLINE void NanRemoveGCEpilogueCallback(
      v8::Isolate::GCEpilogueCallback callback) {
    v8::Isolate::GetCurrent()->RemoveGCEpilogueCallback(callback);
  }

  NAN_INLINE void NanAddGCPrologueCallback(
      v8::Isolate::GCPrologueCallback callback
    , v8::GCType gc_type_filter = v8::kGCTypeAll) {
    v8::Isolate::GetCurrent()->AddGCPrologueCallback(callback, gc_type_filter);
  }

  NAN_INLINE void NanRemoveGCPrologueCallback(
      v8::Isolate::GCPrologueCallback callback) {
    v8::Isolate::GetCurrent()->RemoveGCPrologueCallback(callback);
  }

  NAN_INLINE void NanGetHeapStatistics(
      v8::HeapStatistics *heap_statistics) {
    v8::Isolate::GetCurrent()->GetHeapStatistics(heap_statistics);
  }

  NAN_DEPRECATED NAN_INLINE v8::Local<v8::String> NanSymbol(
      const char* data, int length = -1) {
    return NanNew<v8::String>(data, length);
  }

  template<typename T>
  NAN_INLINE void NanAssignPersistent(
      v8::Persistent<T>& handle
    , v8::Handle<T> obj) {
      handle.Reset(v8::Isolate::GetCurrent(), obj);
  }

  template<typename T>
  NAN_INLINE void NanAssignPersistent(
      v8::Persistent<T>& handle
    , const v8::Persistent<T>& obj) {
      handle.Reset(v8::Isolate::GetCurrent(), obj);
  }

  template<typename T, typename P>
  class _NanWeakCallbackData;

  template<typename T, typename P>
  struct _NanWeakCallbackInfo {
    typedef void (*Callback)(const _NanWeakCallbackData<T, P>& data);
    NAN_INLINE _NanWeakCallbackInfo(v8::Handle<T> handle, P* param, Callback cb)
      : parameter(param), callback(cb) {
       NanAssignPersistent(persistent, handle);
    }

    NAN_INLINE ~_NanWeakCallbackInfo() {
      persistent.Reset();
    }

    P* const parameter;
    Callback const callback;
    v8::Persistent<T> persistent;

   private:
    NAN_DISALLOW_ASSIGN_COPY_MOVE(_NanWeakCallbackInfo)
  };

  template<typename T, typename P>
  class _NanWeakCallbackData {
   public:
    NAN_INLINE _NanWeakCallbackData(_NanWeakCallbackInfo<T, P> *info)
      : info_(info) { }

    NAN_INLINE v8::Local<T> GetValue() const {
      return NanNew(info_->persistent);
    }

    NAN_INLINE P* GetParameter() const { return info_->parameter; }

    NAN_INLINE bool IsNearDeath() const {
      return info_->persistent.IsNearDeath();
    }

    NAN_INLINE void Revive() const;

    NAN_INLINE _NanWeakCallbackInfo<T, P>* GetCallbackInfo() const {
      return info_;
    }

    NAN_DEPRECATED NAN_INLINE void Dispose() const {
    }

   private:
    _NanWeakCallbackInfo<T, P>* info_;
  };

  template<typename T, typename P>
  static void _NanWeakCallbackDispatcher(
    const v8::WeakCallbackData<T, _NanWeakCallbackInfo<T, P> > &data) {
      _NanWeakCallbackInfo<T, P> *info = data.GetParameter();
      _NanWeakCallbackData<T, P> wcbd(info);
      info->callback(wcbd);
      if (wcbd.IsNearDeath()) {
        delete wcbd.GetCallbackInfo();
      }
  }

  template<typename T, typename P>
  NAN_INLINE void _NanWeakCallbackData<T, P>::Revive() const {
      info_->persistent.SetWeak(info_, &_NanWeakCallbackDispatcher<T, P>);
  }

  template<typename T, typename P>
  NAN_INLINE _NanWeakCallbackInfo<T, P>* NanMakeWeakPersistent(
      v8::Handle<T> handle
    , P* parameter
    , typename _NanWeakCallbackInfo<T, P>::Callback callback) {
      _NanWeakCallbackInfo<T, P> *cbinfo =
       new _NanWeakCallbackInfo<T, P>(handle, parameter, callback);
      cbinfo->persistent.SetWeak(cbinfo, &_NanWeakCallbackDispatcher<T, P>);
      return cbinfo;
  }

# define NAN_WEAK_CALLBACK(name)                                               \
    template<typename T, typename P>                                           \
    static void name(const _NanWeakCallbackData<T, P> &data)

# define X(NAME)                                                               \
    NAN_INLINE v8::Local<v8::Value> Nan ## NAME(const char *errmsg) {          \
      NanEscapableScope();                                                     \
      return NanEscapeScope(v8::Exception::NAME(NanNew(errmsg)));              \
    }                                                                          \
                                                                               \
    NAN_INLINE                                                                 \
    v8::Local<v8::Value> Nan ## NAME(v8::Handle<v8::String> errmsg) {          \
      return v8::Exception::NAME(errmsg);                                      \
    }                                                                          \
                                                                               \
    NAN_INLINE void NanThrow ## NAME(const char *errmsg) {                     \
      NanScope();                                                              \
      v8::Isolate::GetCurrent()->ThrowException(                               \
          v8::Exception::NAME(NanNew(errmsg)));                                \
    }                                                                          \
                                                                               \
    NAN_INLINE void NanThrow ## NAME(v8::Handle<v8::String> errmsg) {          \
      NanScope();                                                              \
      v8::Isolate::GetCurrent()->ThrowException(                               \
          v8::Exception::NAME(NanNew(errmsg)));                                \
    }

  X(Error)
  X(RangeError)
  X(ReferenceError)
  X(SyntaxError)
  X(TypeError)

# undef X

  NAN_INLINE void NanThrowError(v8::Handle<v8::Value> error) {
    v8::Isolate::GetCurrent()->ThrowException(error);
  }

  namespace Nan { namespace imp {
    NAN_INLINE v8::Local<v8::Value> E(const char *msg, const int errorNumber) {
      NanEscapableScope();
      v8::Local<v8::Value> err = v8::Exception::Error(NanNew<v8::String>(msg));
      v8::Local<v8::Object> obj = err.As<v8::Object>();
      obj->Set(NanNew<v8::String>("code"), NanNew<v8::Int32>(errorNumber));
      return NanEscapeScope(err);
    }
  }  // end of namespace imp
  }  // end of namespace Nan

  NAN_DEPRECATED NAN_INLINE v8::Local<v8::Value> NanError(
      const char *msg
    , const int errorNumber
  ) {
    return Nan::imp::E(msg, errorNumber);
  }

  NAN_DEPRECATED NAN_INLINE void NanThrowError(
      const char *msg
    , const int errorNumber
  ) {
    NanThrowError(Nan::imp::E(msg, errorNumber));
  }

  template<typename T> NAN_INLINE void NanDisposePersistent(
      v8::Persistent<T> &handle
  ) {
    handle.Reset();
  }

  NAN_INLINE bool NanHasInstance(
      const v8::Persistent<v8::FunctionTemplate>& function_template
    , v8::Handle<v8::Value> value
  ) {
    return NanNew(function_template)->HasInstance(value);
  }

  NAN_DEPRECATED NAN_INLINE v8::Local<v8::Context> NanNewContextHandle(
      v8::ExtensionConfiguration* extensions = NULL
    , v8::Handle<v8::ObjectTemplate> tmpl = v8::Handle<v8::ObjectTemplate>()
    , v8::Handle<v8::Value> obj = v8::Handle<v8::Value>()
  ) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    return v8::Local<v8::Context>::New(
        isolate
      , v8::Context::New(isolate, extensions, tmpl, obj)
    );
  }

  NAN_INLINE v8::Local<NanBoundScript> NanCompileScript(
      v8::Local<v8::String> s
    , const v8::ScriptOrigin& origin
  ) {
    v8::ScriptCompiler::Source source(s, origin);
    return v8::ScriptCompiler::Compile(v8::Isolate::GetCurrent(), &source);
  }

  NAN_INLINE v8::Local<NanBoundScript> NanCompileScript(
      v8::Local<v8::String> s
  ) {
    v8::ScriptCompiler::Source source(s);
    return v8::ScriptCompiler::Compile(v8::Isolate::GetCurrent(), &source);
  }

  NAN_INLINE v8::Local<v8::Value> NanRunScript(
      v8::Handle<NanUnboundScript> script
  ) {
    return script->BindToCurrentContext()->Run();
  }

  NAN_INLINE v8::Local<v8::Value> NanRunScript(
      v8::Handle<NanBoundScript> script
  ) {
    return script->Run();
  }


  template<typename T>
  NAN_INLINE void NanSetIsolateData(
      v8::Isolate *isolate
    , T *data
  ) {
      isolate->SetData(0, data);
  }

  template<typename T>
  NAN_INLINE T *NanGetIsolateData(
      v8::Isolate *isolate
  ) {
      return static_cast<T*>(isolate->GetData(0));
  }

typedef void (*NanFreeCallback)(char *data, void *hint);

#define NAN_METHOD(name) _NAN_METHOD_RETURN_TYPE name(_NAN_METHOD_ARGS)
#define NAN_GETTER(name)                                                       \
    _NAN_GETTER_RETURN_TYPE name(                                              \
        v8::Local<v8::String> property                                         \
      , _NAN_GETTER_ARGS)
#define NAN_SETTER(name)                                                       \
    _NAN_SETTER_RETURN_TYPE name(                                              \
        v8::Local<v8::String> property                                         \
      , v8::Local<v8::Value> value                                             \
      , _NAN_SETTER_ARGS)
#define NAN_PROPERTY_GETTER(name)                                              \
    _NAN_PROPERTY_GETTER_RETURN_TYPE name(                                     \
        v8::Local<v8::String> property                                         \
      , _NAN_PROPERTY_GETTER_ARGS)
#define NAN_PROPERTY_SETTER(name)                                              \
    _NAN_PROPERTY_SETTER_RETURN_TYPE name(                                     \
        v8::Local<v8::String> property                                         \
      , v8::Local<v8::Value> value                                             \
      , _NAN_PROPERTY_SETTER_ARGS)
#define NAN_PROPERTY_ENUMERATOR(name)                                          \
    _NAN_PROPERTY_ENUMERATOR_RETURN_TYPE name(_NAN_PROPERTY_ENUMERATOR_ARGS)
#define NAN_PROPERTY_DELETER(name)                                             \
    _NAN_PROPERTY_DELETER_RETURN_TYPE name(                                    \
        v8::Local<v8::String> property                                         \
      , _NAN_PROPERTY_DELETER_ARGS)
#define NAN_PROPERTY_QUERY(name)                                               \
    _NAN_PROPERTY_QUERY_RETURN_TYPE name(                                      \
        v8::Local<v8::String> property                                         \
      , _NAN_PROPERTY_QUERY_ARGS)
# define NAN_INDEX_GETTER(name)                                                \
    _NAN_INDEX_GETTER_RETURN_TYPE name(uint32_t index, _NAN_INDEX_GETTER_ARGS)
#define NAN_INDEX_SETTER(name)                                                 \
    _NAN_INDEX_SETTER_RETURN_TYPE name(                                        \
        uint32_t index                                                         \
      , v8::Local<v8::Value> value                                             \
      , _NAN_INDEX_SETTER_ARGS)
#define NAN_INDEX_ENUMERATOR(name)                                             \
    _NAN_INDEX_ENUMERATOR_RETURN_TYPE name(_NAN_INDEX_ENUMERATOR_ARGS)
#define NAN_INDEX_DELETER(name)                                                \
    _NAN_INDEX_DELETER_RETURN_TYPE name(                                       \
        uint32_t index                                                         \
      , _NAN_INDEX_DELETER_ARGS)
#define NAN_INDEX_QUERY(name)                                                  \
    _NAN_INDEX_QUERY_RETURN_TYPE name(uint32_t index, _NAN_INDEX_QUERY_ARGS)

class NanCallback {
 public:
  NanCallback() {
    NanScope();
    v8::Local<v8::Object> obj = NanNew<v8::Object>();
    NanAssignPersistent(handle, obj);
  }

  explicit NanCallback(const v8::Handle<v8::Function> &fn) {
    NanScope();
    v8::Local<v8::Object> obj = NanNew<v8::Object>();
    NanAssignPersistent(handle, obj);
    SetFunction(fn);
  }

  ~NanCallback() {
    if (handle.IsEmpty()) return;
    NanDisposePersistent(handle);
  }

  bool operator==(const NanCallback &other) const {
    NanScope();
    v8::Local<v8::Value> a = NanNew(handle)->Get(kCallbackIndex);
    v8::Local<v8::Value> b = NanNew(other.handle)->Get(kCallbackIndex);
    return a->StrictEquals(b);
  }

  bool operator!=(const NanCallback &other) const {
    return !this->operator==(other);
  }

  NAN_INLINE
  v8::Local<v8::Function> operator*() const { return this->GetFunction(); }

  NAN_INLINE v8::Local<v8::Value> operator()(
      v8::Handle<v8::Object> target
    , int argc = 0
    , v8::Handle<v8::Value> argv[] = 0) const {
    return this->Call(target, argc, argv);
  }

  NAN_INLINE v8::Local<v8::Value> operator()(
      int argc = 0
    , v8::Handle<v8::Value> argv[] = 0) const {
    return this->Call(argc, argv);
  }

  NAN_INLINE void SetFunction(const v8::Handle<v8::Function> &fn) {
    NanScope();
    NanNew(handle)->Set(kCallbackIndex, fn);
  }

  NAN_INLINE v8::Local<v8::Function> GetFunction() const {
    NanEscapableScope();
    return NanEscapeScope(NanNew(handle)->Get(kCallbackIndex)
        .As<v8::Function>());
  }

  NAN_INLINE bool IsEmpty() const {
    NanScope();
    return NanNew(handle)->Get(kCallbackIndex)->IsUndefined();
  }

  NAN_INLINE v8::Local<v8::Value>
  Call(v8::Handle<v8::Object> target
     , int argc
     , v8::Handle<v8::Value> argv[]) const {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    return Call_(isolate, target, argc, argv);
  }

  NAN_INLINE v8::Local<v8::Value>
  Call(int argc, v8::Handle<v8::Value> argv[]) const {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    return Call_(isolate, isolate->GetCurrentContext()->Global(), argc, argv);
  }

 private:
  NAN_DISALLOW_ASSIGN_COPY_MOVE(NanCallback)
  v8::Persistent<v8::Object> handle;
  static const uint32_t kCallbackIndex = 0;

  v8::Local<v8::Value> Call_(v8::Isolate *isolate
                           , v8::Handle<v8::Object> target
                           , int argc
                           , v8::Handle<v8::Value> argv[]) const {
    NanEscapableScope();

    v8::Local<v8::Function> callback = NanNew(handle)->
        Get(kCallbackIndex).As<v8::Function>();
      
     return callback->Call(isolate->GetCurrentContext()->Global(), argc, argv);
  }
};

// Used to be a macro, hence the uppercase name.
template <typename TypeName>
inline void NAN_SET_METHOD(const TypeName& recv,
                            const char* name,
                            v8::FunctionCallback callback) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::HandleScope handle_scope(isolate);
  v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate,
                                                                callback);
  v8::Local<v8::Function> fn = t->GetFunction();
  v8::Local<v8::String> fn_name = v8::String::NewFromUtf8(isolate, name);
  fn->SetName(fn_name);
  recv->Set(fn_name, fn);
}

// Used to be a macro, hence the uppercase name.
// Not a template because it only makes sense for FunctionTemplates.
inline void NAN_SET_PROTOTYPE_METHOD(v8::Handle<v8::FunctionTemplate> recv,
                                      const char* name,
                                      v8::FunctionCallback callback) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::HandleScope handle_scope(isolate);
  v8::Handle<v8::Signature> s = v8::Signature::New(isolate, recv);
  v8::Local<v8::FunctionTemplate> t =
      v8::FunctionTemplate::New(isolate, callback, v8::Handle<v8::Value>(), s);
  v8::Local<v8::Function> fn = t->GetFunction();
  recv->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, name), fn);
  v8::Local<v8::String> fn_name = v8::String::NewFromUtf8(isolate, name);
  fn->SetName(fn_name);
}

#endif

