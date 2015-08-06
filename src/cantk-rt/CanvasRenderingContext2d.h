#ifndef _CANVASRENDERINGCONTEXT2D_H
#define _CANVASRENDERINGCONTEXT2D_H

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
#include <v8.h>
#include <nan/nan.h>
#include "Image.h"

using namespace std;
using namespace v8;

struct NVGcontext;

class CanvasRenderingContext2d: public ObjectWrap {
public:
	CanvasRenderingContext2d();
	~CanvasRenderingContext2d();

	void stroke();
	void fill();
	void beginPath();
	void closePath();
	void save();
	void restore();
	void rotate(double angle);
	void scale(double x, double y);
	void translate(double x, double y);
	void transform(double a, double b, double c, double d, double e, double f);
	void setTransform(double a, double b, double c, double d, double e, double f);
	void resetTransform();
	void clip();
	void clipRect(double x, double y, double w, double h);
	void fillText(const char* text, double x, double y);
	void strokeText(const char* text, double x, double y);
	double measureText(const char* text);
	void clearRect(double x, double y, double w, double h);
	void fillRect(double x, double y, double w, double h);
	void strokeRect(double x, double y, double w, double h);
	void drawImage(Image* image, double dx, double dy);
	void drawImage(Image* image, double dx, double dy, double dw, double dh);
	void drawImage(Image* image, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);
	void rect(double x, double y, double w, double h);
	void moveTo(double x, double y);
	void lineTo(double x, double y);
	void bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
	void quadraticCurveTo(double cpx, double cpy, double x, double y);
	void arcTo(double x1, double y1, double x2, double y2, double r);
	void arc(double x, double y, double r, double sAngle, double eAngle, bool counterClockWise);

	double getGlobalAlpha() const;
	void setGlobalAlpha(double globalAlpha);

	int32_t getLineWidth() const;
	void setLineWidth(int32_t lineWidth);

	string getGlobalCompositeOperation() const;
	void setGlobalCompositeOperation(string);

	string getStrokeStyle() const;
	void setStrokeStyle(string strokeStyle);

	string getFillStyle() const;
	void setFillStyle(string fillStyle);

	string getFont() const;
	void setFont(string font);

	string getLineCap() const;
	void setLineCap(string lineCap);
	
	double getMiterLimit() const;
	void setMiterLimit(double miterLimit);

	string getTextBaseline() const;
	void setTextBaseline(string textBaseline);

	string getTextAlign() const;
	void setTextAlign(string textAlign);

	string getLineJoin() const;
	void setLineJoin(string lineJoin);

public:
	static int init();
	static int resize(int w, int h);
	static int beginPaint();
	static int endPaint();
	static int deinit();
	static bool loadImage(const string& url, int& id, int& w, int& h);

	static int width;
	static int height;
	static int sansFont;
	static int sansBoldFont;
	static NVGcontext* shareCtx;

private:
	double _globalAlpha;
	int32_t _lineWidth;
	string _globalCompositeOperation;
	string _strokeStyle;
	string _fillStyle;
	string _font;
	string _lineCap;
	double _miterLimit;
	string _textBaseline;
	string _textAlign;
	string _lineJoin;
	NVGcontext* ctx;
	uint32_t _textBaselineV;
	uint32_t _textAlignV;
	
	static map<string, int> imagesCache;
};

#endif
