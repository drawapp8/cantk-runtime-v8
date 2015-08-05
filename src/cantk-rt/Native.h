#ifndef _NATIVE_BINDING_H
#define _NATIVE_BINDING_H

#include <string>
#include <assert.h>
#include <v8.h>
#include <nan/nan.h>
#include "console.h"
#include "HttpClient.h"

using namespace v8;

void nativeInitBinding(Handle<Object> target);

#endif
