#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <v8.h>
#include <nan/nan.h>

using namespace std;
using namespace v8;


class FileSystem: public ObjectWrap {
public:
	FileSystem();
	~FileSystem();

	bool readAsText(const char* name, char** ret, int* length);

	string getCwd() const;
	void setCwd(string cwd);
private:
};

#endif
