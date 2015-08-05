#ifndef _CANVASBINDING_H
#define _CANVASBINDING_H

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <string.h>

#include <v8.h>
#include <nan/nan.h>

using namespace v8;
void CanvasInitBinding(Handle<Object> target);

#endif
