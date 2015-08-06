#ifndef _LOCATION_H
#define _LOCATION_H

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


class Location: public ObjectWrap {
public:
	Location();
	~Location();


	string getProtocol() const;
	void setProtocol(string protocol);

	string getHost() const;
	void setHost(string host);

	string getHostname() const;
	void setHostname(string hostname);

	string getPath() const;
	void setPath(string path);

	string getHref() const;
	void setHref(string href);

	string getOrigin() const;
	void setOrigin(string origin);

	string getSearch() const;
	void setSearch(string search);

	int32_t getPort() const;
	void setPort(int32_t port);

private:
	string _protocol;
	string _host;
	string _hostname;
	string _path;
	string _href;
	string _origin;
	string _search;
	int32_t _port;
};

#endif
