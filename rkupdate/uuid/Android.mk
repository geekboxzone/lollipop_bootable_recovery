LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
	
LOCAL_PREBUILT_LIBS :=libext2_uuid.a

include $(BUILD_MULTI_PREBUILT)
