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


typedef void (*onContentFunc)(void* ctx, char* buffer, int length);

class FileSystem: public ObjectWrap {
public:
	FileSystem();
	~FileSystem();

	bool readAsText(const char* name, char** ret, int* length);

	string getCwd() const;
	void setCwd(string cwd);
	
	static bool readFile(const char* name, onContentFunc onContent, void* ctx);
	static bool readFileSync(const char* name, char** ret, int* length);

private:
};

#endif
