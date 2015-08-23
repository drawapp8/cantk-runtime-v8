/*
 * File     : canvas_jni.cpp
 * Brief    : canvas jni 
 * Author   : Li XianJing <xianjimli@hotmail.com>
 * Web Site : http://www.tangide.com/
 *
 * Copyright (c) 2015 - 2015 Tangram HD.
 *
**/

#include <uv.h>
#include <jni.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/bitmap.h>

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/time.h>    
#include <unistd.h>
#include "HttpClient.h"
#include "Config.h"
#include "V8Wrapper.h"
#include "queue_event.h"

static int renderTimes = 0;
static double startupTime = 0.0;
static double lastRenderTime = 0.0;

#define JNIAPI extern "C" JNIEXPORT void JNICALL
#define JNIAPIINT extern "C" JNIEXPORT int JNICALL

extern "C" int getpwuid_r(uid_t uid, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result) {
	return -1;
}

static void graphic_context_resize(int w, int h, int dpi) {
	glClearDepthf(1.0f);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	glViewport(0, 0, w, h);

	return;
}

static double getTime () {
	struct timeval tv = {0};

	gettimeofday (&tv, NULL);
	double seconds = tv.tv_sec;
	double dotSeconds = ((double)(tv.tv_usec))/1000000.0;
	double value = seconds + dotSeconds;

	return value;
}

JNIAPI Java_com_tangide_canvas_CanvasJNI_surfaceCreated(JNIEnv * env, jobject obj) {
	int argc = 2;
	struct stat st = {0};

	lastRenderTime = getTime();
	startupTime =  lastRenderTime;

	const char* sysRoot = "/mnt/sdcard-ext/cantk-rt-v8";
	if(!stat(sysRoot, &st) == 0) {
		sysRoot = "/mnt/sdcard/cantk-rt-v8";
	}
	string str = "--sys-root=" + string(sysRoot);
	char* argv[3] = {"android", (char*)str.c_str(), NULL};

	Config::init(argc, argv);
	V8Wrapper::init(argc, argv);

	const char* defaultAppIndex = "/mnt/sdcard-ext/cantk-rt-v8/scripts/cantk/index.html";
	if(!stat(defaultAppIndex, &st) == 0) {
		defaultAppIndex = "/mnt/sdcard/cantk-rt-v8/scripts/cantk/index.html";
	}

	V8Wrapper::loadApp(defaultAppIndex);
}

JNIAPI Java_com_tangide_canvas_CanvasJNI_surfaceChanged(JNIEnv * env, jobject obj,  
	jint width, jint height, jint density)
{
	V8Wrapper::resize(width, height);
	LOGI("Java_com_tangide_canvas_CanvasJNI_surfaceChanged");
}

JNIAPI Java_com_tangide_canvas_CanvasJNI_render(JNIEnv * env, jobject obj)
{
	glClearDepthf(1.0f);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	double t = getTime() - startupTime;
	double dt = t - lastRenderTime;
	lastRenderTime = t;

	uv_run(uv_default_loop(), UV_RUN_NOWAIT);
	HttpClient::pollEvents();
	V8Wrapper::tick(t, dt);

	renderTimes++;

	dt = getTime() - startupTime;
	int fps = renderTimes/dt;
	
	LOGI("fps=%d renderTimes=%d dt=%lf t=%lf CLOCKS_PER_SEC=%d\n", fps, renderTimes, dt, t, CLOCKS_PER_SEC);
}

JNIAPI Java_com_tangide_canvas_CanvasJNI_dispatchKeyDown(JNIEnv * env, jobject obj, jint code) {
	queueKeyEvent(V8_KEY_DOWN, code);
}

JNIAPI Java_com_tangide_canvas_CanvasJNI_dispatchKeyUp(JNIEnv * env, jobject obj, jint code) {
	queueKeyEvent(V8_KEY_UP, code);
}

JNIAPI Java_com_tangide_canvas_CanvasJNI_dispatchTouchEvent(JNIEnv * env, jobject obj, jint action, jint n, 
	jintArray _xs, jintArray _ys) 
{
	vector<Touch> touchs;	
	LOGI("action=%d n=%d\n", action, n);
	jint* xs = env->GetIntArrayElements(_xs,NULL);
	jint* ys = env->GetIntArrayElements(_ys,NULL);

	if(action == 0) {
		action = V8_TOUCH_START;
	}
	else if(action == 1) {
		action = V8_TOUCH_END;
	}
	else {
		action = V8_TOUCH_MOVE;
	}

	for(int i = 0; i < n; i++) {
		int x = xs[i];
		int y = ys[i];
		Touch touch(x, y);
		touchs.push_back(touch);
	}

	env->ReleaseIntArrayElements(_xs, xs, 0);
	env->ReleaseIntArrayElements(_ys, ys, 0);

	queueTouchEvent(action, touchs);
}
