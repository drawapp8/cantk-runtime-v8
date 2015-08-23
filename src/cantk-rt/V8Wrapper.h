#ifndef V8_WRAPPER_H
#define V8_WRAPPER_H

#include <vector>
#include <string>
#include "console.h"
#include <include/v8.h>
#include "nan/nan.h"
#include <include/libplatform/libplatform.h>

using namespace std;
using namespace v8;

#define V8_TOUCH_START 1
#define V8_TOUCH_END 0
#define V8_TOUCH_MOVE 3

#define V8_KEY_DOWN 1
#define V8_KEY_UP 0
#define V8_KEY_REPEAT 2

class Touch {
public:
	Touch(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int x;
	int y;
};

class V8Wrapper {
public:
	V8Wrapper();
	~V8Wrapper();
public:
	static void init(int argc, char* argv[]);
	static void loadApp(const char* appIndex);
	static void deinit();
	static void resize(int w, int h);
	static void tick(double t, double dt);
	static void dispatchEvent(Handle<Object> event);
	static void dispatchPointerEvent(int action, int button, int x, int y);
	static void dispatchTouchEvent(int action, int button, vector<Touch> touchs);
	static void dispatchKeyEvent(int action, int code, int mods, int scancode);

public:
	static Isolate* sIsolate;
	static Platform* sPlatform;
	static Handle<Context> sContext;
	static NanCallback* sTickFunc;
	static NanCallback* sDispatchEventFunc;
};

#endif
