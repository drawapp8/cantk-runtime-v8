#ifndef _IMAGE_H
#define _IMAGE_H

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


class Image: public ObjectWrap {
public:
	Image();
	~Image();

	bool load(const char* src, NanCallback*  onDone);
	bool unload();

	int32_t getId() const;
	void setId(int32_t id);

	string getSrc() const;
	bool setSrc(string src);

	int32_t getWidth() const;
	void setWidth(int32_t width);

	int32_t getHeight() const;
	void setHeight(int32_t height);

private:
	int32_t _id;
	string _src;
	int32_t _width;
	int32_t _height;
};

#endif
