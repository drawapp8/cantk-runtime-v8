#include "console.h"
#include "HttpClient.h"

HttpClient::HttpClient(){
}

HttpClient::~HttpClient(){
}

static string escapeStr(const char*p, int len) {
	string str;
	char buff[2] = {'\0', '\0'};

	for(int i = 0; i < len; i++) {
		char c = p[i];
		if(c == '\"') {
			str += "\\\"";
		}
		else {
			buff[0] = c;
			str += buff;
		}
	}

	return str;
}

static void ev_handler(struct ns_connection *nc, int ev, void *ev_data) {
	struct http_message *hm = (struct http_message *) ev_data;

	switch (ev) {
		case NS_CONNECT: {
			if (* (int *) ev_data != 0) {
				fprintf(stderr, "connect() failed: %s\n", strerror(* (int *) ev_data));
			}
			break;
		}
		case NS_RECV: {
			int len = nc->recv_mbuf.len;
			HttpClient* client = (HttpClient*)(nc->user_data);

			client->callOnProgress(len, len);
			break;
		}
		case NS_HTTP_REPLY: {
			nc->flags |= NSF_CLOSE_IMMEDIATELY;
			HttpClient* client = (HttpClient*)(nc->user_data);
			client->setResponseText(string(hm->body.p, hm->body.len));
			client->setStatus(hm->resp_code);
			int i = 0;
			string str = "[";
			for(i = 0; i < NS_MAX_HTTP_HEADERS; i++) {
				struct ns_str* name  = hm->header_names+i;
				struct ns_str* value = hm->header_values+i;
				if(name->p == NULL || value->p == NULL) break;

				if(i > 0) {
					str += ",";
				}
				str += "{\"name\":\"" + string(name->p, name->len) + "\",\"value\":\"" + escapeStr(value->p, value->len) + "\"}";
			}
			str += "]";
			client->setStatusText(string(hm->resp_status_msg.p, hm->resp_status_msg.len));
			client->setResponseHeaders(str);
			client->callOnDone();
		
			break;
		}
		default: break;
	}

	return;
}

bool HttpClient::send(NanCallback*  onProgress, NanCallback*  onDone) {
	const char* url = this->_url.c_str();
	const char* method = this->_method.length() > 1 ? this->_method.c_str() : "GET";
	const char* headers = this->_requestHeaders.c_str();
	const char* body = this->_requestData.c_str();
	struct ns_connection* con = ns_connect_http(&HttpClient::sNsMgr, ev_handler, method, url, headers, body);
	
	con->user_data = this;
	this->_onDone = onDone;
	this->_onProgress = onProgress;

	return true;
}


string HttpClient::getUrl() const {
	return this->_url;
}

void HttpClient::setUrl(string url) {
	this->_url = url;
}


string HttpClient::getReturnType() const {
	return this->_returnType;
}

void HttpClient::setReturnType(string returnType) {
	this->_returnType = returnType;
}


string HttpClient::getMethod() const {
	return this->_method;
}

void HttpClient::setMethod(string method) {
	this->_method = method;
}


string HttpClient::getRequestHeaders() const {
	return this->_requestHeaders;
}

void HttpClient::setRequestHeaders(string requestHeaders) {
	this->_requestHeaders = requestHeaders;
}


string HttpClient::getRequestData() const {
	return this->_requestData;
}

void HttpClient::setRequestData(string requestData) {
	this->_requestData = requestData;
}


int HttpClient::getStatus() const {
	return this->_status;
}

void HttpClient::setStatus(int status) {
	this->_status = status;
}

string HttpClient::getStatusText() const {
	return this->_statusText;
}

void HttpClient::setStatusText(string statusText) {
	this->_statusText = statusText;
}

string HttpClient::getResponseHeaders() const {
	return this->_responseHeaders;
}

void HttpClient::setResponseHeaders(string responseHeaders) {
	this->_responseHeaders = responseHeaders;
}


string HttpClient::getResponseText() const {
	return this->_responseText;
}

void HttpClient::setResponseText(string responseText) {
	this->_responseText = responseText;
}
	
void HttpClient::callOnDone() {
	NanScope();
	Handle<Value> argv[2];
	argv[0] = NanNew("err");
	argv[1] = NanNew("info");
	this->_onDone->Call(2, argv);
}

void HttpClient::callOnProgress(int total, int finished) {
	NanScope();
	Handle<Value> argv[2];
	Handle<Object> obj = NanNew<Object>();
	
	obj->Set(NanNew("total"), NanNew<Number>(total));
	obj->Set(NanNew("finished"), NanNew<Number>(finished));

	argv[0] = NanNew("success");
	argv[1] = obj;

	this->_onProgress->Call(2, argv);
}

void HttpClient::init() {
	ns_mgr_init(&HttpClient::sNsMgr, NULL);
	LOGI("HttpClient::init");
}

void HttpClient::pollEvents() {
	ns_mgr_poll(&HttpClient::sNsMgr, 0);
}

void HttpClient::deinit() {
	ns_mgr_free(&HttpClient::sNsMgr);
}

struct ns_mgr HttpClient::sNsMgr = {};

