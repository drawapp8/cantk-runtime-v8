#ifndef _LOCATIONBINDING_H
#define _LOCATIONBINDING_H

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <string.h>

#include <v8.h>
#include <nan/nan.h>

using namespace v8;
void LocationInitBinding(Handle<Object> target);

#endif
