#include "Image.h"
#include "CanvasRenderingContext2d.h"

Image::Image(){
}

Image::~Image(){
}


bool Image::load(const char* src, NanCallback*  onDone) {
	int w = 0;
	int h = 0;
	int id = 0;
	NanScope();

	bool ret = CanvasRenderingContext2d::loadImage(src, id, w, h);

	if(ret) {
		this->setId(id);
		this->setWidth(w);
		this->setHeight(h);
	}
	else {
		this->setId(-1);
		this->setWidth(0);
		this->setHeight(0);
	}

	if(onDone) {
		Handle<Value> result = NanNew<Boolean>(ret);
		Handle<Object> imageInfo = NanNew<Object>();
		imageInfo->Set(NanNew<String>("id"), NanNew<Number>(id));
		imageInfo->Set(NanNew<String>("width"), NanNew<Number>(w));
		imageInfo->Set(NanNew<String>("height"), NanNew<Number>(h));
		Handle<Value> argv[2] = {result, imageInfo};

		onDone->Call(2, argv);
	}

	return ret;
}

bool Image::unload() {
}


int32_t Image::getId() const {
	return this->_id;
}

void Image::setId(int32_t id) {
	this->_id = id;
}


string Image::getSrc() const {
	return this->_src;
}

bool Image::setSrc(string src) {
	bool ret = true;
	if(this->_src != src) {
		ret = this->load(src.c_str(), NULL);
	}

	this->_src = src;

	return ret;
}


int32_t Image::getWidth() const {
	return this->_width;
}

void Image::setWidth(int32_t width) {
	this->_width = width;
}


int32_t Image::getHeight() const {
	return this->_height;
}

void Image::setHeight(int32_t height) {
	this->_height = height;
}


