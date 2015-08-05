#include "Config.h"

Config::Config() {
}

Config::~Config() {
}

static string toAsbPath(const char* fileName) {
	if(fileName[0] == '/') {
		return fileName;
	}
	else {
		char cwd[256] = {0};
		char fullFileName[512] = {0};
		getcwd(cwd, sizeof(cwd)-1);
		snprintf(fullFileName, sizeof(fullFileName)-1, "%s/%s", cwd, fileName);

		return fullFileName;
	}
}

static string baseName(const string& fileName) {
	int pos = fileName.find_last_of('/');
	if(pos >= 0) {
		return fileName.substr(pos+1);
	}
	else {
		return fileName;
	}
}

static string dirName(const string& fileName) {
	int pos = fileName.find_last_of('/');
	if(pos >= 0) {
		return fileName.substr(0, pos);
	}
	else {
		return "/";
	}
}

void Config::init(int argc, char* argv[]) {
	const char* str = Config::getStrOption(argc, argv, "--sys-root=", "assets/");
	Config::sysRoot = toAsbPath(str);

	str = Config::getStrOption(argc, argv, "--app-index=", "assets/scripts/test/app-test.js");
	Config::setAppIndex(str);

	Config::screenWidth = Config::getIntOption(argc, argv, "--width=", 800); 
	Config::screenHeight = Config::getIntOption(argc, argv, "--height=", 800); 

	return;
}
	
void Config::setAppIndex(const char* fileName) {
	if(!fileName) return;

	Config::appIndex = toAsbPath(fileName);	
	Config::appRoot = dirName(Config::appIndex.c_str());

	return;
}

string Config::toAppAbsPath(const char* fileName) {
	if(fileName[0] == '/') {
		return fileName;
	}
	else {
		return Config::appRoot + '/' + fileName;
	}
}

string Config::toSysAbsPath(const char* fileName) {
	if(fileName[0] == '/') {
		return fileName;
	}
	else {
		return Config::sysRoot + '/' + fileName;
	}
}

int Config::getIntOption(int argc, char** argv, const char* prefix, int defval) {
	int len = strlen(prefix);
	for(int i = 0; i < argc; i++) {
		const char* iter = argv[i];
		if(strncmp(iter, prefix, len) == 0) {
			int v = atoi(iter + len);
			return v;
		}
	}

	return defval;
}

const char* Config::getStrOption(int argc, char** argv, const char* prefix, const char* defval) {
	int len = strlen(prefix);
	for(int i = 0; i < argc; i++) {
		const char* iter = argv[i];
		if(strncmp(iter, prefix, len) == 0) {
			return (iter + len);
		}
	}

	return defval;
}

string Config::sysRoot = "";
string Config::appRoot = "";
string Config::appIndex = "";
int Config::screenWidth = 0;
int Config::screenHeight = 0;

