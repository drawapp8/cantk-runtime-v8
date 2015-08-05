#include "Canvas.h"

#include "CanvasBinding.h"

NAN_METHOD(newCanvas) {
	NanScope();

	Canvas* obj = new Canvas();
	obj->Wrap(args.This());

	NanReturnValue(args.This());
}

NAN_METHOD(CanvasInit) {
	NanScope();
	if(args.Length() < 1) {
		printf("invalid arguments for init.\n");
		return;
	}
	int32_t type = args[0]->Int32Value();

	Canvas* obj = ObjectWrap::Unwrap<Canvas>(args.This());
	bool retVal =  obj->init(type);
	NanReturnValue(NanNew<Boolean>(retVal));
}

NAN_GETTER(CanvasGetWidth) {
	NanScope();
	Canvas* obj = ObjectWrap::Unwrap<Canvas>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getWidth()));
}

NAN_SETTER(CanvasSetWidth) {
	NanScope();
	Canvas* obj = ObjectWrap::Unwrap<Canvas>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setWidth(nativeValue);
	}else{
		printf("invalid data type for Canvas.width\n");
	}
}

NAN_GETTER(CanvasGetHeight) {
	NanScope();
	Canvas* obj = ObjectWrap::Unwrap<Canvas>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getHeight()));
}

NAN_SETTER(CanvasSetHeight) {
	NanScope();
	Canvas* obj = ObjectWrap::Unwrap<Canvas>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setHeight(nativeValue);
	}else{
		printf("invalid data type for Canvas.height\n");
	}
}

NAN_GETTER(CanvasGetType) {
	NanScope();
	Canvas* obj = ObjectWrap::Unwrap<Canvas>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getType()));
}

NAN_SETTER(CanvasSetType) {
	NanScope();
	Canvas* obj = ObjectWrap::Unwrap<Canvas>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setType(nativeValue);
	}else{
		printf("invalid data type for Canvas.type\n");
	}
}



static Persistent<FunctionTemplate> constructor;
void CanvasInitBinding(Handle<Object> target) {
	NanScope();
	Local<FunctionTemplate> ctor = NanNew<FunctionTemplate>(newCanvas);
	NanAssignPersistent(constructor, ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(NanNew("Canvas"));
	Local<ObjectTemplate> proto = ctor->PrototypeTemplate();
	
	proto->SetAccessor(NanNew("width"), CanvasGetWidth, CanvasSetWidth);
	proto->SetAccessor(NanNew("height"), CanvasGetHeight, CanvasSetHeight);
	proto->SetAccessor(NanNew("type"), CanvasGetType, CanvasSetType);

	NAN_SET_PROTOTYPE_METHOD(ctor, "init", CanvasInit);


	target->Set(NanNew("Canvas"), ctor->GetFunction());

}
