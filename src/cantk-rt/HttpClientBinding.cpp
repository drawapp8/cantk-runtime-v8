#include "HttpClient.h"

#include "HttpClientBinding.h"

NAN_METHOD(newHttpClient) {
	NanScope();

	HttpClient* obj = new HttpClient();
	obj->Wrap(args.This());

	NanReturnValue(args.This());
}

NAN_METHOD(HttpClientSend) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());

	if(args.Length() == 2) {
		NanCallback* onProgress = new NanCallback(args[0].As<Function>());
		NanCallback* onDone = new NanCallback(args[1].As<Function>());

		bool retVal = obj->send(onProgress, onDone);
		NanReturnValue(NanNew<Boolean>(retVal));
		return;
	}

}

NAN_GETTER(HttpClientGetUrl) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	NanReturnValue(NanNew<String>(obj->getUrl()));
}

NAN_SETTER(HttpClientSetUrl) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setUrl(*nativeValue);
	}else{
		printf("invalid data type for HttpClient.url\n");
	}
}

NAN_GETTER(HttpClientGetReturnType) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	NanReturnValue(NanNew<String>(obj->getReturnType()));
}

NAN_SETTER(HttpClientSetReturnType) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setReturnType(*nativeValue);
	}else{
		printf("invalid data type for HttpClient.returnType\n");
	}
}

NAN_GETTER(HttpClientGetMethod) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	NanReturnValue(NanNew<String>(obj->getMethod()));
}

NAN_SETTER(HttpClientSetMethod) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setMethod(*nativeValue);
	}else{
		printf("invalid data type for HttpClient.method\n");
	}
}

NAN_GETTER(HttpClientGetRequestHeaders) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	NanReturnValue(NanNew<String>(obj->getRequestHeaders()));
}

NAN_SETTER(HttpClientSetRequestHeaders) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setRequestHeaders(*nativeValue);
	}else{
		printf("invalid data type for HttpClient.requestHeaders\n");
	}
}

NAN_GETTER(HttpClientGetRequestData) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	NanReturnValue(NanNew<String>(obj->getRequestData()));
}

NAN_SETTER(HttpClientSetRequestData) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setRequestData(*nativeValue);
	}else{
		printf("invalid data type for HttpClient.requestData\n");
	}
}

NAN_GETTER(HttpClientGetStatus) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getStatus()));
}

NAN_SETTER(HttpClientSetStatus) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setStatus(nativeValue);
	}else{
		printf("invalid data type for HttpClient.status\n");
	}
}

NAN_GETTER(HttpClientGetStatusText) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	NanReturnValue(NanNew<String>(obj->getStatusText()));
}

NAN_SETTER(HttpClientSetStatusText) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setStatusText(*nativeValue);
	}else{
		printf("invalid data type for HttpClient.statusText\n");
	}
}

NAN_GETTER(HttpClientGetResponseHeaders) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	NanReturnValue(NanNew<String>(obj->getResponseHeaders()));
}

NAN_SETTER(HttpClientSetResponseHeaders) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setResponseHeaders(*nativeValue);
	}else{
		printf("invalid data type for HttpClient.responseHeaders\n");
	}
}

NAN_GETTER(HttpClientGetResponseText) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	NanReturnValue(NanNew<String>(obj->getResponseText()));
}

NAN_SETTER(HttpClientSetResponseText) {
	NanScope();
	HttpClient* obj = ObjectWrap::Unwrap<HttpClient>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setResponseText(*nativeValue);
	}else{
		printf("invalid data type for HttpClient.responseText\n");
	}
}



static Persistent<FunctionTemplate> constructor;
void HttpClientInitBinding(Handle<Object> target) {
	NanScope();
	Local<FunctionTemplate> ctor = NanNew<FunctionTemplate>(newHttpClient);
	NanAssignPersistent(constructor, ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(NanNew("HttpClient"));
	Local<ObjectTemplate> proto = ctor->PrototypeTemplate();
	
	proto->SetAccessor(NanNew("url"), HttpClientGetUrl, HttpClientSetUrl);
	proto->SetAccessor(NanNew("returnType"), HttpClientGetReturnType, HttpClientSetReturnType);
	proto->SetAccessor(NanNew("method"), HttpClientGetMethod, HttpClientSetMethod);
	proto->SetAccessor(NanNew("requestHeaders"), HttpClientGetRequestHeaders, HttpClientSetRequestHeaders);
	proto->SetAccessor(NanNew("requestData"), HttpClientGetRequestData, HttpClientSetRequestData);
	proto->SetAccessor(NanNew("status"), HttpClientGetStatus, HttpClientSetStatus);
	proto->SetAccessor(NanNew("statusText"), HttpClientGetStatusText, HttpClientSetStatusText);
	proto->SetAccessor(NanNew("responseHeaders"), HttpClientGetResponseHeaders, HttpClientSetResponseHeaders);
	proto->SetAccessor(NanNew("responseText"), HttpClientGetResponseText, HttpClientSetResponseText);

	NAN_SET_PROTOTYPE_METHOD(ctor, "send", HttpClientSend);


	target->Set(NanNew("HttpClient"), ctor->GetFunction());

	HttpClient::init();
}
