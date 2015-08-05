#ifndef _SCREEN_H
#define _SCREEN_H

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <v8.h>
#include <nan/nan.h>

using namespace std;
using namespace v8;


class Screen: public ObjectWrap {
public:
	Screen();
	~Screen();


	int32_t getColorDepth() const;
	void setColorDepth(int32_t colorDepth);

	int32_t getPixelDepth() const;
	void setPixelDepth(int32_t pixelDepth);

	int32_t getAvailLeft() const;
	void setAvailLeft(int32_t availLeft);

	int32_t getAvailTop() const;
	void setAvailTop(int32_t availTop);

	int32_t getAvailWidth() const;
	void setAvailWidth(int32_t availWidth);

	int32_t getAvailHeight() const;
	void setAvailHeight(int32_t availHeight);

	int32_t getWidth() const;
	void setWidth(int32_t width);

	int32_t getHeight() const;
	void setHeight(int32_t height);

private:
	int32_t _colorDepth;
	int32_t _pixelDepth;
	int32_t _availLeft;
	int32_t _availTop;
	int32_t _availWidth;
	int32_t _availHeight;
	int32_t _width;
	int32_t _height;
};

#endif
