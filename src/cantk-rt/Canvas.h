#ifndef _CANVAS_H
#define _CANVAS_H

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


class Canvas: public ObjectWrap {
public:
	Canvas();
	~Canvas();

	bool init(int32_t type);

	int32_t getWidth() const;
	void setWidth(int32_t width);

	int32_t getHeight() const;
	void setHeight(int32_t height);

	int32_t getType() const;
	void setType(int32_t type);

private:
	int32_t _width;
	int32_t _height;
	int32_t _type;
};

#endif
