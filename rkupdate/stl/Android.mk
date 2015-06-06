LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
	
LOCAL_PREBUILT_LIBS := libgnustl_static.a

include $(BUILD_MULTI_PREBUILT)
