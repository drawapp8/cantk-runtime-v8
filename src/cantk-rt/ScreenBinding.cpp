#include "Screen.h"

#include "ScreenBinding.h"

NAN_METHOD(newScreen) {
	NanScope();

	Screen* obj = new Screen();
	obj->Wrap(args.This());

	NanReturnValue(args.This());
}

NAN_GETTER(ScreenGetColorDepth) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getColorDepth()));
}

NAN_SETTER(ScreenSetColorDepth) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setColorDepth(nativeValue);
	}else{
		printf("invalid data type for Screen.colorDepth\n");
	}
}

NAN_GETTER(ScreenGetPixelDepth) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getPixelDepth()));
}

NAN_SETTER(ScreenSetPixelDepth) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setPixelDepth(nativeValue);
	}else{
		printf("invalid data type for Screen.pixelDepth\n");
	}
}

NAN_GETTER(ScreenGetAvailLeft) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getAvailLeft()));
}

NAN_SETTER(ScreenSetAvailLeft) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setAvailLeft(nativeValue);
	}else{
		printf("invalid data type for Screen.availLeft\n");
	}
}

NAN_GETTER(ScreenGetAvailTop) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getAvailTop()));
}

NAN_SETTER(ScreenSetAvailTop) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setAvailTop(nativeValue);
	}else{
		printf("invalid data type for Screen.availTop\n");
	}
}

NAN_GETTER(ScreenGetAvailWidth) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getAvailWidth()));
}

NAN_SETTER(ScreenSetAvailWidth) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setAvailWidth(nativeValue);
	}else{
		printf("invalid data type for Screen.availWidth\n");
	}
}

NAN_GETTER(ScreenGetAvailHeight) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getAvailHeight()));
}

NAN_SETTER(ScreenSetAvailHeight) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setAvailHeight(nativeValue);
	}else{
		printf("invalid data type for Screen.availHeight\n");
	}
}

NAN_GETTER(ScreenGetWidth) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getWidth()));
}

NAN_SETTER(ScreenSetWidth) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setWidth(nativeValue);
	}else{
		printf("invalid data type for Screen.width\n");
	}
}

NAN_GETTER(ScreenGetHeight) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getHeight()));
}

NAN_SETTER(ScreenSetHeight) {
	NanScope();
	Screen* obj = ObjectWrap::Unwrap<Screen>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setHeight(nativeValue);
	}else{
		printf("invalid data type for Screen.height\n");
	}
}



static Persistent<FunctionTemplate> constructor;
void ScreenInitBinding(Handle<Object> target) {
	NanScope();
	Local<FunctionTemplate> ctor = NanNew<FunctionTemplate>(newScreen);
	NanAssignPersistent(constructor, ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(NanNew("Screen"));
	Local<ObjectTemplate> proto = ctor->PrototypeTemplate();
	
	proto->SetAccessor(NanNew("colorDepth"), ScreenGetColorDepth, ScreenSetColorDepth);
	proto->SetAccessor(NanNew("pixelDepth"), ScreenGetPixelDepth, ScreenSetPixelDepth);
	proto->SetAccessor(NanNew("availLeft"), ScreenGetAvailLeft, ScreenSetAvailLeft);
	proto->SetAccessor(NanNew("availTop"), ScreenGetAvailTop, ScreenSetAvailTop);
	proto->SetAccessor(NanNew("availWidth"), ScreenGetAvailWidth, ScreenSetAvailWidth);
	proto->SetAccessor(NanNew("availHeight"), ScreenGetAvailHeight, ScreenSetAvailHeight);
	proto->SetAccessor(NanNew("width"), ScreenGetWidth, ScreenSetWidth);
	proto->SetAccessor(NanNew("height"), ScreenGetHeight, ScreenSetHeight);



	target->Set(NanNew("Screen"), ctor->GetFunction());

}
