LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := VCMP
LOCAL_LDLIBS := -llog -lEGL -lGLESv2
FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/game/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/util/*.cpp)

LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_CPPFLAGS += -D_ARM_ -D_RAKNET_THREADSAFE
LOCAL_CPPFLAGS += -w -pthread -fpack-struct=1 -Wall -fdiagnostics-color=auto -O2 -ffast-math -std=c++11
include $(BUILD_SHARED_LIBRARY)
