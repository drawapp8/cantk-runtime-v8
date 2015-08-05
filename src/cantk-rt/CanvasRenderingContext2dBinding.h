#ifndef _CANVASRENDERINGCONTEXT2DBINDING_H
#define _CANVASRENDERINGCONTEXT2DBINDING_H

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <string.h>

#include <v8.h>
#include <nan/nan.h>

using namespace v8;
void CanvasRenderingContext2dInitBinding(Handle<Object> target);

#endif
