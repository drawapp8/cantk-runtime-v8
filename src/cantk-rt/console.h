#ifndef CONSOLE_H
#define CONSOLE_H

#ifndef LOGI
#ifdef ANDROID
#include <android/log.h>
#define  LOG_TAG    "com.tangide.canvas"
#define  CONSOLE_LOG(...)  __android_log_print(ANDROID_LOG_INFO,"V8Console:",__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGV(...)
#else
#include <stdio.h>
#define CONSOLE_LOG(...) printf(__VA_ARGS__)
#define LOGI(...) printf(__VA_ARGS__)
#define LOGE(...) printf(__VA_ARGS__)
#define LOGV(...) printf(__VA_ARGS__)
#endif

#endif//LOGI

#endif//CONSOLE_H
