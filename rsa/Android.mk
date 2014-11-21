LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
	
LOCAL_PREBUILT_LIBS :=librsa.a

include $(BUILD_MULTI_PREBUILT)
