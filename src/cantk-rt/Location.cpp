#include "Location.h"
#include "Config.h"

Location::Location(){
	this->setProtocol("file:");
	this->setPath("/");
}

Location::~Location(){
}



string Location::getProtocol() const {
	return this->_protocol;
}

void Location::setProtocol(string protocol) {
	this->_protocol = protocol;
}


string Location::getHost() const {
	if(this->_protocol == "file:") {
		return Config::appRoot + "/";
	}

	return this->_host;
}

void Location::setHost(string host) {
	this->_host = host;
}


string Location::getHostname() const {
	return this->_hostname;
}

void Location::setHostname(string hostname) {
	this->_hostname = hostname;
}


string Location::getPath() const {
	return this->_path;
}

void Location::setPath(string path) {
	this->_path = path;
}


string Location::getHref() const {
	return this->_href;
}

void Location::setHref(string href) {
	this->_href = href;
}


string Location::getOrigin() const {
	return this->_origin;
}

void Location::setOrigin(string origin) {
	this->_origin = origin;
}


string Location::getSearch() const {
	return this->_search;
}

void Location::setSearch(string search) {
	this->_search = search;
}


int32_t Location::getPort() const {
	return this->_port;
}

void Location::setPort(int32_t port) {
	this->_port = port;
}


