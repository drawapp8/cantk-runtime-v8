
#include "V8Wrapper.h"

#ifndef QUEUE_EVENT_H
#define QUEUE_EVENT_H

void queueKeyEvent(int action, int code);
void queueTouchEvent(int action, const vector<Touch>& touchs);

#endif//QUEUE_EVENT_H
