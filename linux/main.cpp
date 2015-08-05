#include <stdio.h>
#ifdef NANOVG_GLEW
#  include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#include <uv.h>
#include "Native.h"
#include "V8Wrapper.h"
#include "Config.h"

void errorcb(int error, const char* desc)
{
	printf("GLFW error %d: %s\n", error, desc);
}

static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	V8Wrapper::dispatchKeyEvent(action, key, mods, scancode);
}

static void onMouseButton(GLFWwindow* window, int button, int action, int mods) {
	double x = 0, y = 0;;
	
	glfwGetCursorPos(window, &x, &y);
	V8Wrapper::dispatchPointerEvent(action, button, x, y);
}

static void onMouseMove(GLFWwindow* window, double x, double y) {
	V8Wrapper::dispatchPointerEvent(3, 0, x, y);
}

typedef struct _AppInfo {
	double lastEventTime;
	double lastUptateTime;
	GLFWwindow* window;
	int width;
	int height;
	int shouldQuit;
}AppInfo;

static void pollEvents(uv_idle_t* handle, int status) {
	AppInfo* info = (AppInfo*)handle->data;
	double lastEventTime = info->lastEventTime;
	double lastUptateTime = info->lastUptateTime;

	GLFWwindow* window = info->window;

	glfwPollEvents();
	HttpClient::pollEvents();

	if(glfwWindowShouldClose(window)) {
		uv_idle_stop(handle);
		info->shouldQuit = 1;
		return;
	}
	
	double t, dt;
	
	t = glfwGetTime();
	info->lastEventTime = t;
	dt = t - lastUptateTime;
	if(dt < 0.016) {
	//	return;
	}
	info->lastUptateTime = t;

	dt = t - lastEventTime;

	int winWidth, winHeight;
	int fbWidth, fbHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

	if(winWidth != info->width || winHeight != info->height) {
		V8Wrapper::resize(winWidth, winHeight);
		info->width = winWidth;
		info->height = winHeight;
	}

	// Update and render
	glViewport(0, 0, fbWidth, fbHeight);glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
	glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
////////////////////////////////////////////////////////////////////////////////////
	V8Wrapper::tick(t, dt);
////////////////////////////////////////////////////////////////////////////////////

	glfwSwapBuffers(window);

	return;
}

int main(int argc, char** argv)
{
	AppInfo info = {};
	GLFWwindow* window = NULL;
	Config::init(argc, argv);

	int w = Config::screenWidth;
	int h = Config::screenHeight;
	
	if (!glfwInit()) {
		printf("Failed to init GLFW.");
		return -1;
	}

	glfwSetErrorCallback(errorcb);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(w, h, "CanTK Runtime", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, onKey);
	glfwSetCursorPosCallback(window, onMouseMove);
	glfwSetMouseButtonCallback(window, onMouseButton);
	glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
		printf("Could not init glew.\n");
		return -1;
	}

	glfwSwapInterval(0);
	glfwSetTime(0);

	info.width = w;
	info.height = h;
	info.window = window;
	info.shouldQuit = 0;
	info.lastEventTime = glfwGetTime();
/////////////////////////////////////////////////////
	V8Wrapper::init(argc, argv);
	V8Wrapper::loadApp(NULL);
	V8Wrapper::resize(w, h);
	
	uv_idle_t idle;
	uv_loop_t* loop = uv_default_loop();

	uv_idle_init(loop, &idle);
	uv_idle_start(&idle, pollEvents);

	idle.data = &info;

#if 0	
	int count = 0;
	while(!info.shouldQuit) {
		count++;
		printf("%d\n", count);
		uv_run(loop, UV_RUN_NOWAIT);
	}
#else
	uv_run(loop, UV_RUN_DEFAULT);
#endif
	glfwTerminate();
///////////////////////////////////////////////	
	V8Wrapper::deinit();
///////////////////////////////////////////////	

	return 0;
}
