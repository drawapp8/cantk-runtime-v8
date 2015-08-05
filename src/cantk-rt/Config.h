#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include "console.h"

using namespace std;

class Config {
public:
	Config();
	~Config();

public:
	static void init(int argc, char* argv[]);
	static string toAppAbsPath(const char* fileName);
	static string toSysAbsPath(const char* fileName);
	static void setAppIndex(const char* fileName);

	static int getIntOption(int argc, char** argv, const char* prefix, int defval);
	static const char* getStrOption(int argc, char** argv, const char* prefix, const char* defval);

	static int screenWidth;
	static int screenHeight;
	static string sysRoot;
	static string appRoot;
	static string appIndex;
};

#endif//_CONFIG_H
