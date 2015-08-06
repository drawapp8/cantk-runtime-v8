#include "Location.h"

#include "LocationBinding.h"

NAN_METHOD(newLocation) {
	NanScope();

	Location* obj = new Location();
	obj->Wrap(args.This());

	NanReturnValue(args.This());
}

NAN_GETTER(LocationGetProtocol) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	NanReturnValue(NanNew<String>(obj->getProtocol()));
}

NAN_SETTER(LocationSetProtocol) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setProtocol(*nativeValue);
	}else{
		printf("invalid data type for Location.protocol\n");
	}
}

NAN_GETTER(LocationGetHost) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	NanReturnValue(NanNew<String>(obj->getHost()));
}

NAN_SETTER(LocationSetHost) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setHost(*nativeValue);
	}else{
		printf("invalid data type for Location.host\n");
	}
}

NAN_GETTER(LocationGetHostname) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	NanReturnValue(NanNew<String>(obj->getHostname()));
}

NAN_SETTER(LocationSetHostname) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setHostname(*nativeValue);
	}else{
		printf("invalid data type for Location.hostname\n");
	}
}

NAN_GETTER(LocationGetPath) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	NanReturnValue(NanNew<String>(obj->getPath()));
}

NAN_SETTER(LocationSetPath) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setPath(*nativeValue);
	}else{
		printf("invalid data type for Location.path\n");
	}
}

NAN_GETTER(LocationGetHref) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	NanReturnValue(NanNew<String>(obj->getHref()));
}

NAN_SETTER(LocationSetHref) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setHref(*nativeValue);
	}else{
		printf("invalid data type for Location.href\n");
	}
}

NAN_GETTER(LocationGetOrigin) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	NanReturnValue(NanNew<String>(obj->getOrigin()));
}

NAN_SETTER(LocationSetOrigin) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setOrigin(*nativeValue);
	}else{
		printf("invalid data type for Location.origin\n");
	}
}

NAN_GETTER(LocationGetSearch) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	NanReturnValue(NanNew<String>(obj->getSearch()));
}

NAN_SETTER(LocationSetSearch) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setSearch(*nativeValue);
	}else{
		printf("invalid data type for Location.search\n");
	}
}

NAN_GETTER(LocationGetPort) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getPort()));
}

NAN_SETTER(LocationSetPort) {
	NanScope();
	Location* obj = ObjectWrap::Unwrap<Location>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setPort(nativeValue);
	}else{
		printf("invalid data type for Location.port\n");
	}
}



static Persistent<FunctionTemplate> constructor;
void LocationInitBinding(Handle<Object> target) {
	NanScope();
	Local<FunctionTemplate> ctor = NanNew<FunctionTemplate>(newLocation);
	NanAssignPersistent(constructor, ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(NanNew("Location"));
	Local<ObjectTemplate> proto = ctor->PrototypeTemplate();
	
	proto->SetAccessor(NanNew("protocol"), LocationGetProtocol, LocationSetProtocol);
	proto->SetAccessor(NanNew("host"), LocationGetHost, LocationSetHost);
	proto->SetAccessor(NanNew("hostname"), LocationGetHostname, LocationSetHostname);
	proto->SetAccessor(NanNew("path"), LocationGetPath, LocationSetPath);
	proto->SetAccessor(NanNew("href"), LocationGetHref, LocationSetHref);
	proto->SetAccessor(NanNew("origin"), LocationGetOrigin, LocationSetOrigin);
	proto->SetAccessor(NanNew("search"), LocationGetSearch, LocationSetSearch);
	proto->SetAccessor(NanNew("port"), LocationGetPort, LocationSetPort);



	target->Set(NanNew("Location"), ctor->GetFunction());

}
