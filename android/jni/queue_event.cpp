#include "uv.h"
#include "queue_event.h"

class QKeyEvent {
public:
	QKeyEvent(int action, int code) {
		this->action = action;
		this->code = code;
	}
public:
	int action;
	int code;
};

static void keyEventHandler(uv_idle_t* handle) {
	QKeyEvent* event = (QKeyEvent*)handle->data;

	uv_idle_stop(handle);
	delete handle;
	delete event;
}

void queueKeyEvent(int action, int code) {
	uv_idle_t* idle = new uv_idle_t();
	QKeyEvent* event = new QKeyEvent(action, code);
	
	V8Wrapper::dispatchKeyEvent(event->action, event->code, 0, 0);

	idle->data = event;
	uv_idle_init(uv_default_loop(), idle);
	uv_idle_start(idle, keyEventHandler);
}

class QTouchEvent {
public:
	QTouchEvent(int action, vector<Touch> touchs) {
		this->action = action;
		this->touchs = touchs;
	}

public:
	int action;
	vector<Touch> touchs;
};

static void touchEventHandler(uv_idle_t* handle) {
	QTouchEvent* event = (QTouchEvent*)handle->data;
	
	V8Wrapper::dispatchTouchEvent(event->action, 0, event->touchs);

	uv_idle_stop(handle);
	delete handle;
	delete event;
}

void queueTouchEvent(int action, const vector<Touch>& touchs) {
	uv_idle_t* idle = new uv_idle_t();
	QTouchEvent* event = new QTouchEvent(action, touchs);

	idle->data = event;
	uv_idle_init(uv_default_loop(), idle);
	uv_idle_start(idle, touchEventHandler);

	return;
}
