#ifndef V8_WRAPPER_H
#define V8_WRAPPER_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <include/v8.h>
#include "console.h"
#include <include/libplatform/libplatform.h>

using namespace std;
using namespace v8;


class V8Wrapper {
public:
	V8Wrapper();
	~V8Wrapper();
public:
	static void init(int argc, char* argv[]);
	static void deinit();
	static void resize(int w, int h);
	static void tick(double t, double dt);
	static void dispatchEvent(Handle<Object> event);
	static void dispatchPointerEvent(int action, int button, int x, int y);
	static void dispatchKeyEvent(int action, int code, int mods, int scancode);

public:
	static Isolate* sIsolate;
	static Platform* sPlatform;
	static Handle<Context> sContext;
	static Persistent<Function> sTickFunc;
	static Persistent<Function> sDispatchEventFunc;
};

int getIntOption(int argc, char** argv, const char* prefix, int defval);
const char* getStrOption(int argc, char** argv, const char* prefix, const char* defval);

#endif
