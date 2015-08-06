#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Native.h"
#include "CanvasBinding.h"
#include "ScreenBinding.h"
#include "ImageBinding.h"
#include "LocationBinding.h"
#include "FileSystemBinding.h"
#include "HttpClientBinding.h"
#include "CanvasRenderingContext2dBinding.h"

static void getNamedProperty(Local<String> property, const PropertyCallbackInfo<Value>& info) {
}

static void setNamedProperty(Local<String> property, Local<Value> value,
	const PropertyCallbackInfo<Value>& info) {

}	

void nativeInitBinding(Handle<Object> target) {
	Handle<Object> window = NanNew<Object>();

//	Handle<Object> v8RealGlobal = Handle<Object>::Cast(target->GetPrototype()); 
//	v8RealGlobal->Set(NanNew("window"), v8RealGlobal); 

	target->Set(NanNew("window"), target);

	ScreenInitBinding(target);
	ImageInitBinding(target);
	LocationInitBinding(target);
	CanvasInitBinding(target);
	FileSystemInitBinding(target);
	HttpClientInitBinding(target);
	CanvasRenderingContext2dInitBinding(target);

	return;
}

