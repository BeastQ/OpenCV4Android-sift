LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := nonfree
LOCAL_SRC_FILES := libnonfree.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := opencv_java_prebuilt
LOCAL_SRC_FILES := libopencv_java3.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
include Z:\\android\\OpenCV-3.1.0-android-sdk\\OpenCV-android-sdk\\sdk\\native\\jni\\OpenCV.mk
LOCAL_MODULE    := SIFT
LOCAL_CFLAGS    := -Werror -O3 -ffast-math
LOCAL_LDLIBS    += -llog -ldl
LOCAL_SHARED_LIBRARIES := nonfree opencv_java_prebuilt
LOCAL_SRC_FILES := SIFT.cpp
include $(BUILD_SHARED_LIBRARY)