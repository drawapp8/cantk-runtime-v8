
#include "V8Wrapper.h"

#ifndef QUEUE_EVENT_H
#define QUEUE_EVENT_H

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

class QEvent {
public:
	QEvent(int type, void* data) {
		this->type = type;
		this->data = data;
	}

	enum {
		Q_EVENT_NONE = 0,
		Q_EVENT_KEY = 1,
		Q_EVENT_TOUCH = 2
	};
public:
	int type;
	void* data;
};

#endif//QUEUE_EVENT_H
