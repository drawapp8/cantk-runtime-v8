#NDK_TOOLCHAIN_VERSION=clang

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := v8_base
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_SRC_FILES := libs/arm/libv8_base.a
else ifeq ($(TARGET_ARCH_ABI),armeabi)
    LOCAL_SRC_FILES := libs/arm/libv8_base.a
else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_SRC_FILES := libs/x86/libv8_base.a
endif
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := v8_libplatform
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_SRC_FILES := libs/arm/libv8_libplatform.a
else ifeq ($(TARGET_ARCH_ABI),armeabi)
    LOCAL_SRC_FILES := libs/arm/libv8_libplatform.a
else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_SRC_FILES := libs/x86/libv8_libplatform.a
endif
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE    := v8_libbase
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_SRC_FILES := libs/arm/libv8_libbase.a
else ifeq ($(TARGET_ARCH_ABI),armeabi)
    LOCAL_SRC_FILES := libs/arm/libv8_libbase.a
else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_SRC_FILES := libs/x86/libv8_libbase.a
endif
include $(PREBUILT_STATIC_LIBRARY)



include $(CLEAR_VARS)
LOCAL_MODULE    := v8_nosnapshot
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_SRC_FILES := libs/arm/libv8_nosnapshot.a
else ifeq ($(TARGET_ARCH_ABI),armeabi)
    LOCAL_SRC_FILES := libs/arm/libv8_nosnapshot.a
else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_SRC_FILES := libs/x86/libv8_nosnapshot.a
endif
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := zip
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_SRC_FILES := libs/arm/libzip.a
else ifeq ($(TARGET_ARCH_ABI),armeabi)
    LOCAL_SRC_FILES := libs/arm/libzip.a
else ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_SRC_FILES := libs/x86/libzip.a
endif
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)

THIRD_SRC=../../src/third/
CANTK_RT_SRC=../../src/cantk-rt/

LOCAL_CFLAGS    :=  -DNANOVG_GLES2_IMPLEMENTATION -DDEBUG -DANDROID  -Os \
	-I/work/android/android-4.4/frameworks/native/include \
	-I$(THIRD_SRC)/nanovg/src/ -I$(THIRD_SRC) -I$(CANTK_RT_SRC)

LOCAL_CPPFLAGS += -std=c++11 -DNANOVG_GLES2 -I./$(THIRD_SRC)/nanovg/src/ -I$(THIRD_SRC) -Wwrite-strings

LOCAL_MODULE    := cantkrt 
LOCAL_SRC_FILES := canvas_jni.cpp  \
	$(THIRD_SRC)/fossa/fossa.c \
	$(THIRD_SRC)/nanovg/src/nanovg.c \
	$(CANTK_RT_SRC)/Config.cpp \
	$(CANTK_RT_SRC)/HttpClientBinding.cpp \
	$(CANTK_RT_SRC)/CanvasBinding.cpp \
	$(CANTK_RT_SRC)/FileSystem.cpp \
	$(CANTK_RT_SRC)/V8Wrapper.cpp \
	$(CANTK_RT_SRC)/CanvasRenderingContext2d.cpp \
	$(CANTK_RT_SRC)/Native.cpp \
	$(CANTK_RT_SRC)/HttpClient.cpp \
	$(CANTK_RT_SRC)/FileSystemBinding.cpp \
	$(CANTK_RT_SRC)/Canvas.cpp \
	$(CANTK_RT_SRC)/Location.cpp \
	$(CANTK_RT_SRC)/LocationBinding.cpp \
	$(CANTK_RT_SRC)/Image.cpp \
	$(CANTK_RT_SRC)/ImageBinding.cpp \
	$(CANTK_RT_SRC)/Screen.cpp \
	$(CANTK_RT_SRC)/ScreenBinding.cpp \
	$(CANTK_RT_SRC)/CanvasRenderingContext2dBinding.cpp \
	$(CANTK_RT_SRC)/color_parser.c \
	$(CANTK_RT_SRC)/utils.c 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDLIBS    := -llog -landroid -lz -lGLESv2 -lc -ljnigraphics
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
LOCAL_STATIC_LIBRARIES := v8_base v8_libbase v8_libplatform v8_nosnapshot zip android-ndk-profiler
#LOCAL_CFLAGS += -pg -DNDK_PROFILER_ENABLED
else
LOCAL_STATIC_LIBRARIES := v8_base v8_libbase v8_libplatform v8_nosnapshot zip
endif
include $(BUILD_SHARED_LIBRARY)

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
# at the end of Android.mk
#$(call import-module,android-ndk-profiler)
endif

