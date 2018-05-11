LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := duktape
LOCAL_SRC_FILES := duktape/src/duktape.c
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_LDLIBS    := -lm -llog
LOCAL_SHARED_LIBRARIES := libduktape
LOCAL_C_INCLUDES := -I$(LOCAL_PATH)/duktape/src/ -I$(LOCAL_PATH)/
LOCAL_MODULE := kk-duktape
LOCAL_SRC_FILES := kk.c kk-duktape.c
include $(BUILD_SHARED_LIBRARY)


