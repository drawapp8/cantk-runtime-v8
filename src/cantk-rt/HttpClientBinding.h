#ifndef _HTTPCLIENTBINDING_H
#define _HTTPCLIENTBINDING_H

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <string.h>

#include <v8.h>
#include <nan/nan.h>

using namespace v8;
void HttpClientInitBinding(Handle<Object> target);

#endif
