#ifndef _IMAGEBINDING_H
#define _IMAGEBINDING_H

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <string.h>

#include <v8.h>
#include <nan/nan.h>

using namespace v8;
void ImageInitBinding(Handle<Object> target);

#endif
