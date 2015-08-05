#ifndef _NATIVE_BINDING_H
#define _NATIVE_BINDING_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <v8.h>
#include <nan/nan.h>
#include "HttpClient.h"

using namespace v8;

void nativeInitBinding(Handle<Object> target);

#endif
