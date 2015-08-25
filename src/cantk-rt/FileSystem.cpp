#include <errno.h>
#include <unistd.h>
#include <uv.h>
#include <console.h>
#include "FileSystem.h"

FileSystem::FileSystem(){
}

FileSystem::~FileSystem(){
}

bool FileSystem::readAsText(const char* name, char** ret, int* length) {
	return FileSystem::readFileSync(name, ret, length);
}

typedef struct _FsReadReq {
	void* ctx;
	uv_file fd;
	char* buff;
	onContentFunc onContent;
}FsReadReq;

static void onReadDone(uv_fs_t *req) {
	FsReadReq* readReq = (FsReadReq*)req->reserved[3];

	if(req->result > 0) {
		readReq->buff[req->result] = '\0';
		readReq->onContent(readReq->ctx, readReq->buff, req->result);
	}
	else {
		readReq->onContent(readReq->ctx, NULL, 0);
	}

	uv_fs_req_cleanup(req);
	uv_fs_close(uv_default_loop(), req, readReq->fd, NULL);
	uv_fs_req_cleanup(req);
	delete req;
}


bool FileSystem::readFile(const char* name, onContentFunc onContent, void* ctx) {
	uv_fs_t* req = new uv_fs_t;
	uv_loop_t* loop = uv_default_loop();
	uv_file fd = uv_fs_open(loop, req, name, O_RDONLY, 0, NULL);	

	if(fd < 0) {
  		LOGI("open file failed: %s %d\n", name, errno);

  		return false;
	}
	
	uv_fs_req_cleanup(req);
	uv_fs_fstat(loop, req, fd, NULL);
	int size = req->statbuf.st_size;

	char* buff = new char[size+1];
	uv_buf_t iov = uv_buf_init(buff, size);
	uv_fs_req_cleanup(req);

	FsReadReq* readReq = new FsReadReq;
	req->reserved[3] = readReq;
	readReq->fd = fd;
	readReq->ctx = ctx;
	readReq->buff = buff;
	readReq->onContent = onContent;

	uv_fs_read(loop, req, fd, &iov, 1, -1, onReadDone);

	return true;
}

bool FileSystem::readFileSync(const char* name, char** ret, int* length) {
	uv_fs_t req;
	uv_loop_t* loop = uv_default_loop();
	uv_file fd = uv_fs_open(loop, &req, name, O_RDONLY, 0, NULL);	

	if(fd < 0) {
  		LOGI("open file failed: %s %d\n", name, errno);

  		return false;
	}
	
	uv_fs_req_cleanup(&req);
	uv_fs_fstat(loop, &req, fd, NULL);
	int size = req.statbuf.st_size;

	char* buff = new char[size+1];
	uv_buf_t iov = uv_buf_init(buff, size);
	uv_fs_req_cleanup(&req);
	uv_fs_read(loop, &req, fd, &iov, 1, -1, NULL);
	uv_fs_close(loop, &req, fd, NULL);

	buff[size] = '\0';
	*ret = buff;
	*length = size;
  
	return true;
}

string FileSystem::getCwd() const {
	char cwd[1024] = {0};
	getcwd(cwd, sizeof(cwd));

	return string(cwd);
}

void FileSystem::setCwd(string cwd) {
	chdir(cwd.c_str());
}


