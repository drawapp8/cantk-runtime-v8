#ifdef NANOVG_GLES2
#define nvgCreateContext nvgCreateGLES2 
#define nvgDeleteContext nvgDeleteGLES2
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define NANOVG_GL2_IMPLEMENTATION
#define nvgCreateContext nvgCreateGL2
#define nvgDeleteContext nvgDeleteGL2
#endif
#include "utils.h"
#include "nanovg.h"
#include "nanovg_gl.h"
#include "color_parser.h"

#include "Config.h"
#include <fossa/fossa.h>
#include "CanvasRenderingContext2d.h"


CanvasRenderingContext2d::CanvasRenderingContext2d(){
	this->_textBaselineV = NVG_ALIGN_MIDDLE;
	this->_textAlignV = NVG_ALIGN_CENTER;
	this->ctx = CanvasRenderingContext2d::shareCtx;
}

CanvasRenderingContext2d::~CanvasRenderingContext2d(){
}


void CanvasRenderingContext2d::stroke() {
	if(_strokeStyle.length() > 0) {
		nvgStroke(ctx);
	}
}

void CanvasRenderingContext2d::fill() {
	nvgFill(ctx);
}

void CanvasRenderingContext2d::beginPath() {
	nvgBeginPath(ctx);
}

void CanvasRenderingContext2d::closePath() {
	nvgClosePath(ctx);
}

void CanvasRenderingContext2d::save() {
	nvgSave(ctx);
}

void CanvasRenderingContext2d::restore() {
	nvgRestore(ctx);
}

void CanvasRenderingContext2d::rotate(double angle) {
	nvgRotate(ctx, angle);
}

void CanvasRenderingContext2d::scale(double x, double y) {
	nvgScale(ctx, x, y);
}

void CanvasRenderingContext2d::translate(double x, double y) {
	nvgTranslate(ctx, x, y);
}

void CanvasRenderingContext2d::transform(double a, double b, double c, double d, double e, double f) {
	nvgTransform(ctx, a, b, c, d, e, f);
}

void CanvasRenderingContext2d::setTransform(double a, double b, double c, double d, double e, double f) {
	nvgResetTransform(ctx);
	nvgTransform(ctx, a, b, c, d, e, f);
}

void CanvasRenderingContext2d::resetTransform() {
	nvgResetTransform(ctx);
}

void CanvasRenderingContext2d::clip() {
	//TODO
}

void CanvasRenderingContext2d::clipRect(double x, double y, double w, double h) {
	//TODO
}

void CanvasRenderingContext2d::fillText(const char* text, double x, double y) {
	nvgTextAlign(ctx, this->_textAlignV | this->_textBaselineV);
	nvgText(ctx, x, y, text, NULL);
}

void CanvasRenderingContext2d::strokeText(const char* text, double x, double y) {
	nvgTextAlign(ctx, this->_textAlignV | this->_textBaselineV);
	nvgText(ctx, x, y, text, NULL);
}

double CanvasRenderingContext2d::measureText(const char* text) {
	float bounds[4] = {0,0,0,0};
	nvgTextBounds(ctx, 0, 0, text, NULL, bounds);

	if(bounds) {
		double width = bounds[2] - bounds[0];

		return width;
	}
	else {
		return 0;
	}
}

void CanvasRenderingContext2d::clearRect(double x, double y, double w, double h) {
	nvgBeginPath(ctx);
	nvgRect(ctx, x, y, w, h);
	nvgClosePath(ctx);
	nvgFill(ctx);
}

void CanvasRenderingContext2d::fillRect(double x, double y, double w, double h) {
	nvgBeginPath(ctx);
	nvgRect(ctx, x, y, w, h);
	nvgClosePath(ctx);
	nvgFill(ctx);
}

void CanvasRenderingContext2d::strokeRect(double x, double y, double w, double h) {
	nvgBeginPath(ctx);
	nvgRect(ctx, x, y, w, h);
	nvgClosePath(ctx);
	nvgStroke(ctx);
}

void CanvasRenderingContext2d::drawImage(Image* image, double dx, double dy) {
	double w = image->getWidth();
	double h = image->getHeight();

	this->drawImage(image, 0, 0, w, h, dx, dy, w, h);
}

void CanvasRenderingContext2d::drawImage(Image* image, double dx, double dy, double dw, double dh) {
	double w = image->getWidth();
	double h = image->getHeight();

	this->drawImage(image, 0, 0, w, h, dx, dy, dw, dh);
}

void CanvasRenderingContext2d::drawImage(Image* image, double sx, double sy, double sw, double sh, 
		double dx, double dy, double dw, double dh) {
	int iw = 0;
	int ih = 0;
	int img = image->getId();
	double scaleX = (float)dw/sw;
	double scaleY = (float)dh/sh;
	nvgImageSize(ctx, img, &iw, &ih);
	NVGpaint imgPaint = nvgImagePattern(ctx, 0, 0, iw, ih, 0, img, 1);

	nvgSave(ctx);
	nvgBeginPath(ctx);
	nvgTranslate(ctx, dx-(sx*scaleX), dy-(sy*scaleY));
	nvgScale(ctx, scaleX, scaleY);
	nvgRect(ctx, sx, sy, sw, sh);	
	nvgFillPaint(ctx, imgPaint);
	nvgClosePath(ctx);
	nvgFill(ctx);
	nvgRestore(ctx);
}

void CanvasRenderingContext2d::rect(double x, double y, double w, double h) {
	nvgRect(ctx, x, y, w, h);
}

void CanvasRenderingContext2d::moveTo(double x, double y) {
	nvgMoveTo(ctx, x, y);
}

void CanvasRenderingContext2d::lineTo(double x, double y) {
	nvgLineTo(ctx, x, y);
}

void CanvasRenderingContext2d::bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y) {
	nvgBezierTo(ctx, cp1x, cp1y, cp2x, cp2y, x, y);
}

void CanvasRenderingContext2d::quadraticCurveTo(double cpx, double cpy, double x, double y) {
	nvgQuadTo(ctx, cpx, cpy, x, y);
}

void CanvasRenderingContext2d::arcTo(double x1, double y1, double x2, double y2, double r) {
	nvgArcTo(ctx, x1, y1, x2, y2, r);
}

void CanvasRenderingContext2d::arc(double x, double y, double r, double sAngle, double eAngle, bool counterClockWise) {
	nvgArc(ctx, x, y, r, sAngle, eAngle, counterClockWise);
}


double CanvasRenderingContext2d::getGlobalAlpha() const {
	return this->_globalAlpha;
}

void CanvasRenderingContext2d::setGlobalAlpha(double globalAlpha) {
	nvgGlobalAlpha(ctx, globalAlpha);
	this->_globalAlpha = globalAlpha;
}


int32_t CanvasRenderingContext2d::getLineWidth() const {
	return this->_lineWidth;
}

void CanvasRenderingContext2d::setLineWidth(int32_t lineWidth) {
	nvgStrokeWidth(ctx, lineWidth);
	this->_lineWidth = lineWidth;
}


string CanvasRenderingContext2d::getGlobalCompositeOperation() const {
	return this->_globalCompositeOperation;
}

void CanvasRenderingContext2d::setGlobalCompositeOperation(string globalCompositeOperation) {
	this->_globalCompositeOperation = globalCompositeOperation;
}


string CanvasRenderingContext2d::getStrokeStyle() const {
	return this->_strokeStyle;
}

void CanvasRenderingContext2d::setStrokeStyle(string strokeStyle) {
	NVGcolor  color;
	const char* str = strokeStyle.c_str();
	ColorRGBA rgba = parseColor(str ? str : "#00000000");
	color.r = rgba.r/255.f;
	color.g = rgba.g/255.f;
	color.b = rgba.b/255.f;
	color.a = rgba.a/255.f;

	nvgStrokeColor(ctx, color);
	this->_strokeStyle = strokeStyle;
}


string CanvasRenderingContext2d::getFillStyle() const {
	return this->_fillStyle;
}

void CanvasRenderingContext2d::setFillStyle(string fillStyle) {
	NVGcolor  color;
	const char* str = fillStyle.c_str();
	ColorRGBA rgba = parseColor(str ? str : "#00000000");
	color.r = rgba.r/255.f;
	color.g = rgba.g/255.f;
	color.b = rgba.b/255.f;
	color.a = rgba.a/255.f;

	nvgFillColor(ctx, color);
	this->_fillStyle = fillStyle;
}


string CanvasRenderingContext2d::getFont() const {
	return this->_font;
}

void CanvasRenderingContext2d::setFont(string font) {
	const char* str = font.c_str();
	int fontSize = parseFontSize(str);
	int bold = font.find("bold") >= 0;

	nvgFontSize(ctx, fontSize);
	if(bold) {
		nvgFontFace(ctx, "sans");
	}
	else {
		nvgFontFace(ctx, "sans-bold");
	}

	this->_font = font;
}


string CanvasRenderingContext2d::getLineCap() const {
	return this->_lineCap;
}

void CanvasRenderingContext2d::setLineCap(string lineCap) {
	int lineCapV = NVG_BUTT;
	if(lineCap.length() < 1) {
		lineCapV = NVG_BUTT;
	}
	else if(lineCap[0] == 's') {
		lineCapV = NVG_SQUARE;
	}
	else if(lineCap[0] == 'r') {
		lineCapV = NVG_ROUND;
	}

	nvgLineCap(ctx, lineCapV);
	this->_lineCap = lineCap;
}

double CanvasRenderingContext2d::getMiterLimit() const {
	return this->_miterLimit;
}

void CanvasRenderingContext2d::setMiterLimit(double miterLimit) {
	this->_miterLimit = miterLimit;
	nvgMiterLimit(ctx, miterLimit);
}

string CanvasRenderingContext2d::getTextBaseline() const {
	return this->_textBaseline;
}

void CanvasRenderingContext2d::setTextBaseline(string textBaseline) {
	enum NVGalign textBaselineV = NVG_ALIGN_TOP;
	if(textBaseline.length() < 1 || textBaseline[0] == 't') {
		textBaselineV = NVG_ALIGN_TOP;
	}
	else if(textBaseline[0] == 'b') {
		textBaselineV = NVG_ALIGN_BOTTOM;
	}
	else {
		textBaselineV = NVG_ALIGN_MIDDLE;
	}

	this->_textBaselineV = textBaselineV;
	this->_textBaseline = textBaseline;
}


string CanvasRenderingContext2d::getTextAlign() const {
	return this->_textAlign;
}

void CanvasRenderingContext2d::setTextAlign(string textAlign) {
	enum NVGalign textAlignV = NVG_ALIGN_LEFT;
	if(textAlign.length() < 1) {
		textAlignV = NVG_ALIGN_LEFT;
	}
	else if(textAlign[0] == 'r') {
		textAlignV = NVG_ALIGN_RIGHT;
	}
	else {
		textAlignV = NVG_ALIGN_CENTER;
	}

	this->_textAlignV = textAlignV;
	this->_textAlign = textAlign;
}


string CanvasRenderingContext2d::getLineJoin() const {
	return this->_lineJoin;
}

void CanvasRenderingContext2d::setLineJoin(string lineJoin) {
	int lineJoinV = NVG_MITER;

	if(lineJoin.length() < 1) {
		lineJoinV = NVG_MITER;
	}
	else if(lineJoin[0] == 'r') {
		lineJoinV = NVG_ROUND;
	}
	else if(lineJoin[0] == 'b') {
		lineJoinV = NVG_BEVEL;
	}

	nvgLineJoin(ctx, lineJoinV);

	this->_lineJoin = lineJoin;
}


int CanvasRenderingContext2d::init() {
	NVGcontext* ctx = nvgCreateContext(0);
	CanvasRenderingContext2d::shareCtx = ctx;

	string sansFont = Config::toSysAbsPath("font/BreakTheSilence.ttf");
	string sansBoldFont = Config::toSysAbsPath("font/Simpleton-Gothic.ttf");
	CanvasRenderingContext2d::sansFont = nvgCreateFont(ctx, "sans", sansFont.c_str());
	CanvasRenderingContext2d::sansBoldFont = nvgCreateFont(ctx, "sans-bold", sansBoldFont.c_str());

	LOGI("sansFont:%s\n", sansFont.c_str());	
	LOGI("sansBoldFont:%s\n", sansBoldFont.c_str());	

	return 0;
}

int CanvasRenderingContext2d::resize(int w, int h) {
	CanvasRenderingContext2d::width = w;
	CanvasRenderingContext2d::height = h;

	return 0;
}

int CanvasRenderingContext2d::beginPaint() {
	int w = CanvasRenderingContext2d::width;
	int h = CanvasRenderingContext2d::height;
	nvgBeginFrame(CanvasRenderingContext2d::shareCtx, w, h, 1);

	return 0;
}

int CanvasRenderingContext2d::endPaint(){
	nvgEndFrame(CanvasRenderingContext2d::shareCtx);
}

int CanvasRenderingContext2d::deinit() {
	nvgDeleteContext(CanvasRenderingContext2d::shareCtx);
}

bool CanvasRenderingContext2d::loadImage(const string& url, int& id, int& w, int& h) {
	map<string, int>::const_iterator iter = CanvasRenderingContext2d::imagesCache.find(url);

	if(iter == CanvasRenderingContext2d::imagesCache.end()) {
		int offset = url.find(";base64,");
		if(offset > 0) {
			int n = url.length();
			char* buff = new char[n];
			const char* data = url.c_str() + offset + 8;
			int len = base64_decode((unsigned char*)data, n-offset-8, buff); 
			id = nvgCreateImageMem(CanvasRenderingContext2d::shareCtx, 0, (unsigned char*)buff, len);
			delete buff;
		}
		else {
			const char* fileName = url.c_str();
			if(url.find("file://") == 0) {
				fileName += 7;
			}
			id = nvgCreateImage(CanvasRenderingContext2d::shareCtx, fileName, 0);
		}
	}
	else {
		id = iter->second;
		LOGI("found image in cache:%d\n", id);
	}

	if(id > 0) {
		CanvasRenderingContext2d::imagesCache[url] = id;
		nvgImageSize(CanvasRenderingContext2d::shareCtx, id, &w, &h);
	}

	if(url.length() < 1024) {
		printf("id=%d w=%d h=%d %s\n", id, w, h, url.c_str());
	}

	return id > 0;
}

int CanvasRenderingContext2d::width = 0;
int CanvasRenderingContext2d::height = 0;
int CanvasRenderingContext2d::sansFont = 0;
int CanvasRenderingContext2d::sansBoldFont = 0;
NVGcontext* CanvasRenderingContext2d::shareCtx = NULL;
map<string, int> CanvasRenderingContext2d::imagesCache;
