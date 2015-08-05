#include "Screen.h"
#include "CanvasRenderingContext2d.h"

Screen::Screen(){
}

Screen::~Screen(){
}



int32_t Screen::getColorDepth() const {
	return 24;
}

void Screen::setColorDepth(int32_t colorDepth) {
}


int32_t Screen::getPixelDepth() const {
	return 24;
}

void Screen::setPixelDepth(int32_t pixelDepth) {
}


int32_t Screen::getAvailLeft() const {
	return this->_availLeft;
}

void Screen::setAvailLeft(int32_t availLeft) {
}


int32_t Screen::getAvailTop() const {
	return this->_availTop;
}

void Screen::setAvailTop(int32_t availTop) {
}


int32_t Screen::getAvailWidth() const {
	return CanvasRenderingContext2d::width;
}

void Screen::setAvailWidth(int32_t availWidth) {
}


int32_t Screen::getAvailHeight() const {
	return CanvasRenderingContext2d::height;
}

void Screen::setAvailHeight(int32_t availHeight) {
}


int32_t Screen::getWidth() const {
	return CanvasRenderingContext2d::width;
}

void Screen::setWidth(int32_t width) {
	this->_width = width;
}


int32_t Screen::getHeight() const {
	return CanvasRenderingContext2d::height;
}

void Screen::setHeight(int32_t height) {
}


