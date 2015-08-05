#include <math.h>
#include "CanvasRenderingContext2d.h"

#include "CanvasRenderingContext2dBinding.h"

NAN_METHOD(newCanvasRenderingContext2d) {
	NanScope();

	CanvasRenderingContext2d* obj = new CanvasRenderingContext2d();
	obj->Wrap(args.This());

	NanReturnValue(args.This());
}

NAN_METHOD(CanvasRenderingContext2dStroke) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 0) {

		obj->stroke();
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dFill) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 0) {

		obj->fill();
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dBeginPath) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 0) {

		obj->beginPath();
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dClosePath) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 0) {

		obj->closePath();
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dSave) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 0) {

		obj->save();
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dRestore) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 0) {

		obj->restore();
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dRotate) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 1) {
		double angle = args[0]->NumberValue();

		obj->rotate(angle);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dScale) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 2) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();

		obj->scale(x, y);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dTranslate) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 2) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();

		obj->translate(x, y);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dTransform) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 6) {
		double a = args[0]->NumberValue();
		double b = args[1]->NumberValue();
		double c = args[2]->NumberValue();
		double d = args[3]->NumberValue();
		double e = args[4]->NumberValue();
		double f = args[5]->NumberValue();

		obj->transform(a, b, c, d, e, f);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dSetTransform) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 6) {
		double a = args[0]->NumberValue();
		double b = args[1]->NumberValue();
		double c = args[2]->NumberValue();
		double d = args[3]->NumberValue();
		double e = args[4]->NumberValue();
		double f = args[5]->NumberValue();

		obj->setTransform(a, b, c, d, e, f);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dResetTransform) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 0) {

		obj->resetTransform();
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dClip) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 0) {

		obj->clip();
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dClipRect) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 4) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();
		double w = args[2]->NumberValue();
		double h = args[3]->NumberValue();

		obj->clipRect(x, y, w, h);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dFillText) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 3) {
		v8::String::Utf8Value text(args[0]);
		double x = args[1]->NumberValue();
		double y = args[2]->NumberValue();

		obj->fillText(*text, x, y);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dStrokeText) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 3) {
		v8::String::Utf8Value text(args[0]);
		double x = args[1]->NumberValue();
		double y = args[2]->NumberValue();

		obj->strokeText(*text, x, y);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dMeasureText) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 1) {
		v8::String::Utf8Value text(args[0]);

		double retVal = obj->measureText(*text);
		NanReturnValue(NanNew<Number>(retVal));
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dClearRect) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 4) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();
		double w = args[2]->NumberValue();
		double h = args[3]->NumberValue();

		obj->clearRect(x, y, w, h);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dFillRect) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 4) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();
		double w = args[2]->NumberValue();
		double h = args[3]->NumberValue();

		obj->fillRect(x, y, w, h);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dStrokeRect) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 4) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();
		double w = args[2]->NumberValue();
		double h = args[3]->NumberValue();

		obj->strokeRect(x, y, w, h);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dDrawImage) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 3) {
		Local<Object> imageObj = args[0]->ToObject();
		Image* image = ObjectWrap::Unwrap<Image>(imageObj);
		double dx = args[1]->NumberValue();
		double dy = args[2]->NumberValue();

		obj->drawImage(image, dx, dy);
		NanReturnUndefined();
		return;
	}

	if(args.Length() == 5) {
		Local<Object> imageObj = args[0]->ToObject();
		Image* image = ObjectWrap::Unwrap<Image>(imageObj);
		double dx = args[1]->NumberValue();
		double dy = args[2]->NumberValue();
		double dw = args[3]->NumberValue();
		double dh = args[4]->NumberValue();

		obj->drawImage(image, dx, dy, dw, dh);
		NanReturnUndefined();
		return;
	}

	if(args.Length() == 9) {
		Local<Object> imageObj = args[0]->ToObject();
		Image* image = ObjectWrap::Unwrap<Image>(imageObj);
		double sx = args[1]->NumberValue();
		double sy = args[2]->NumberValue();
		double sw = args[3]->NumberValue();
		double sh = args[4]->NumberValue();
		double dx = args[5]->NumberValue();
		double dy = args[6]->NumberValue();
		double dw = args[7]->NumberValue();
		double dh = args[8]->NumberValue();

		obj->drawImage(image, sx, sy, sw, sh, dx, dy, dw, dh);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dRect) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 4) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();
		double w = args[2]->NumberValue();
		double h = args[3]->NumberValue();

		obj->rect(x, y, w, h);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dMoveTo) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 2) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();

		obj->moveTo(x, y);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dLineTo) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 2) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();

		obj->lineTo(x, y);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dBezierCurveTo) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 6) {
		double cp1x = args[0]->NumberValue();
		double cp1y = args[1]->NumberValue();
		double cp2x = args[2]->NumberValue();
		double cp2y = args[3]->NumberValue();
		double x = args[4]->NumberValue();
		double y = args[5]->NumberValue();

		obj->bezierCurveTo(cp1x, cp1y, cp2x, cp2y, x, y);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dQuadraticCurveTo) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 4) {
		double cpx = args[0]->NumberValue();
		double cpy = args[1]->NumberValue();
		double x = args[2]->NumberValue();
		double y = args[3]->NumberValue();

		obj->quadraticCurveTo(cpx, cpy, x, y);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dArcTo) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	if(args.Length() == 5) {
		double x1 = args[0]->NumberValue();
		double y1 = args[1]->NumberValue();
		double x2 = args[2]->NumberValue();
		double y2 = args[3]->NumberValue();
		double r = args[4]->NumberValue();

		obj->arcTo(x1, y1, x2, y2, r);
		NanReturnUndefined();
		return;
	}

}

NAN_METHOD(CanvasRenderingContext2dArc) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());

	int argsNr = args.Length();
	if(argsNr == 5 || argsNr == 6) {
		double x = args[0]->NumberValue();
		double y = args[1]->NumberValue();
		double r = args[2]->NumberValue();
		double sAngle = args[3]->NumberValue();
		double eAngle = args[4]->NumberValue();
		bool counterClockWise = argsNr == 6 ? args[5]->BooleanValue() : false;
		
		if(fabs(eAngle - sAngle) > 6.28) counterClockWise = true;

		obj->arc(x, y, r, sAngle, eAngle, counterClockWise);
		NanReturnUndefined();
		return;
	}

}

NAN_GETTER(CanvasRenderingContext2dGetGlobalAlpha) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<Number>(obj->getGlobalAlpha()));
}

NAN_SETTER(CanvasRenderingContext2dSetGlobalAlpha) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsNumber()) {
		double nativeValue = value->NumberValue();
		obj->setGlobalAlpha(nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.globalAlpha\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetLineWidth) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<Int32>(obj->getLineWidth()));
}

NAN_SETTER(CanvasRenderingContext2dSetLineWidth) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsInt32()) {
		int32_t nativeValue = value->Int32Value();
		obj->setLineWidth(nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.lineWidth\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetGlobalCompositeOperation) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<String>(obj->getGlobalCompositeOperation()));
}

NAN_SETTER(CanvasRenderingContext2dSetGlobalCompositeOperation) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setGlobalCompositeOperation(*nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.globalCompositeOperation\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetStrokeStyle) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<String>(obj->getStrokeStyle()));
}

NAN_SETTER(CanvasRenderingContext2dSetStrokeStyle) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setStrokeStyle(*nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.strokeStyle\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetFillStyle) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<String>(obj->getFillStyle()));
}

NAN_SETTER(CanvasRenderingContext2dSetFillStyle) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setFillStyle(*nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.fillStyle\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetFont) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<String>(obj->getFont()));
}

NAN_SETTER(CanvasRenderingContext2dSetFont) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setFont(*nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.font\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetLineCap) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<String>(obj->getLineCap()));
}

NAN_SETTER(CanvasRenderingContext2dSetLineCap) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setLineCap(*nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.lineCap\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetMiterLimit) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<Number>(obj->getMiterLimit()));
}

NAN_SETTER(CanvasRenderingContext2dSetMiterLimit) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsNumber()) {
		double nativeValue = value->NumberValue();
		obj->setMiterLimit(nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.miterLimit\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetTextBaseline) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<String>(obj->getTextBaseline()));
}

NAN_SETTER(CanvasRenderingContext2dSetTextBaseline) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setTextBaseline(*nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.textBaseline\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetTextAlign) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<String>(obj->getTextAlign()));
}

NAN_SETTER(CanvasRenderingContext2dSetTextAlign) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setTextAlign(*nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.textAlign\n");
	}
}

NAN_GETTER(CanvasRenderingContext2dGetLineJoin) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	NanReturnValue(NanNew<String>(obj->getLineJoin()));
}

NAN_SETTER(CanvasRenderingContext2dSetLineJoin) {
	NanScope();
	CanvasRenderingContext2d* obj = ObjectWrap::Unwrap<CanvasRenderingContext2d>(args.This());
	if (value->IsString()) {
		v8::String::Utf8Value nativeValue(value);
		obj->setLineJoin(*nativeValue);
	}else{
		printf("invalid data type for CanvasRenderingContext2d.lineJoin\n");
	}
}



static Persistent<FunctionTemplate> constructor;
void CanvasRenderingContext2dInitBinding(Handle<Object> target) {
	NanScope();
	Local<FunctionTemplate> ctor = NanNew<FunctionTemplate>(newCanvasRenderingContext2d);
	NanAssignPersistent(constructor, ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(NanNew("CanvasRenderingContext2d"));
	Local<ObjectTemplate> proto = ctor->PrototypeTemplate();
	
	proto->SetAccessor(NanNew("globalAlpha"), CanvasRenderingContext2dGetGlobalAlpha, CanvasRenderingContext2dSetGlobalAlpha);
	proto->SetAccessor(NanNew("lineWidth"), CanvasRenderingContext2dGetLineWidth, CanvasRenderingContext2dSetLineWidth);
	proto->SetAccessor(NanNew("globalCompositeOperation"), CanvasRenderingContext2dGetGlobalCompositeOperation, CanvasRenderingContext2dSetGlobalCompositeOperation);
	proto->SetAccessor(NanNew("strokeStyle"), CanvasRenderingContext2dGetStrokeStyle, CanvasRenderingContext2dSetStrokeStyle);
	proto->SetAccessor(NanNew("fillStyle"), CanvasRenderingContext2dGetFillStyle, CanvasRenderingContext2dSetFillStyle);
	proto->SetAccessor(NanNew("font"), CanvasRenderingContext2dGetFont, CanvasRenderingContext2dSetFont);
	proto->SetAccessor(NanNew("lineCap"), CanvasRenderingContext2dGetLineCap, CanvasRenderingContext2dSetLineCap);
	proto->SetAccessor(NanNew("miterLimit"), CanvasRenderingContext2dGetMiterLimit, CanvasRenderingContext2dSetMiterLimit);
	proto->SetAccessor(NanNew("textBaseline"), CanvasRenderingContext2dGetTextBaseline, CanvasRenderingContext2dSetTextBaseline);
	proto->SetAccessor(NanNew("textAlign"), CanvasRenderingContext2dGetTextAlign, CanvasRenderingContext2dSetTextAlign);
	proto->SetAccessor(NanNew("lineJoin"), CanvasRenderingContext2dGetLineJoin, CanvasRenderingContext2dSetLineJoin);

	NAN_SET_PROTOTYPE_METHOD(ctor, "stroke", CanvasRenderingContext2dStroke);
	NAN_SET_PROTOTYPE_METHOD(ctor, "fill", CanvasRenderingContext2dFill);
	NAN_SET_PROTOTYPE_METHOD(ctor, "beginPath", CanvasRenderingContext2dBeginPath);
	NAN_SET_PROTOTYPE_METHOD(ctor, "closePath", CanvasRenderingContext2dClosePath);
	NAN_SET_PROTOTYPE_METHOD(ctor, "save", CanvasRenderingContext2dSave);
	NAN_SET_PROTOTYPE_METHOD(ctor, "restore", CanvasRenderingContext2dRestore);
	NAN_SET_PROTOTYPE_METHOD(ctor, "rotate", CanvasRenderingContext2dRotate);
	NAN_SET_PROTOTYPE_METHOD(ctor, "scale", CanvasRenderingContext2dScale);
	NAN_SET_PROTOTYPE_METHOD(ctor, "translate", CanvasRenderingContext2dTranslate);
	NAN_SET_PROTOTYPE_METHOD(ctor, "transform", CanvasRenderingContext2dTransform);
	NAN_SET_PROTOTYPE_METHOD(ctor, "setTransform", CanvasRenderingContext2dSetTransform);
	NAN_SET_PROTOTYPE_METHOD(ctor, "resetTransform", CanvasRenderingContext2dResetTransform);
	NAN_SET_PROTOTYPE_METHOD(ctor, "clip", CanvasRenderingContext2dClip);
	NAN_SET_PROTOTYPE_METHOD(ctor, "clipRect", CanvasRenderingContext2dClipRect);
	NAN_SET_PROTOTYPE_METHOD(ctor, "fillText", CanvasRenderingContext2dFillText);
	NAN_SET_PROTOTYPE_METHOD(ctor, "strokeText", CanvasRenderingContext2dStrokeText);
	NAN_SET_PROTOTYPE_METHOD(ctor, "measureText", CanvasRenderingContext2dMeasureText);
	NAN_SET_PROTOTYPE_METHOD(ctor, "clearRect", CanvasRenderingContext2dClearRect);
	NAN_SET_PROTOTYPE_METHOD(ctor, "fillRect", CanvasRenderingContext2dFillRect);
	NAN_SET_PROTOTYPE_METHOD(ctor, "strokeRect", CanvasRenderingContext2dStrokeRect);
	NAN_SET_PROTOTYPE_METHOD(ctor, "drawImage", CanvasRenderingContext2dDrawImage);
	NAN_SET_PROTOTYPE_METHOD(ctor, "rect", CanvasRenderingContext2dRect);
	NAN_SET_PROTOTYPE_METHOD(ctor, "moveTo", CanvasRenderingContext2dMoveTo);
	NAN_SET_PROTOTYPE_METHOD(ctor, "lineTo", CanvasRenderingContext2dLineTo);
	NAN_SET_PROTOTYPE_METHOD(ctor, "bezierCurveTo", CanvasRenderingContext2dBezierCurveTo);
	NAN_SET_PROTOTYPE_METHOD(ctor, "quadraticCurveTo", CanvasRenderingContext2dQuadraticCurveTo);
	NAN_SET_PROTOTYPE_METHOD(ctor, "arcTo", CanvasRenderingContext2dArcTo);
	NAN_SET_PROTOTYPE_METHOD(ctor, "arc", CanvasRenderingContext2dArc);


	target->Set(NanNew("CanvasRenderingContext2d"), ctor->GetFunction());

}
