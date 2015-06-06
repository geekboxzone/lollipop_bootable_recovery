LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
	
LOCAL_PREBUILT_LIBS :=librkrsa.a

include $(BUILD_MULTI_PREBUILT)
