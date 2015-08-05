#ifndef _FILESYSTEMBINDING_H
#define _FILESYSTEMBINDING_H

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <string.h>

#include <v8.h>
#include <nan/nan.h>

using namespace v8;
void FileSystemInitBinding(Handle<Object> target);

#endif
