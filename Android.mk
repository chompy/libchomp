LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libchomp

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/src \
	$(LOCAL_PATH)/src/asset \
	$(LOCAL_PATH)/src/exception \
	$(LOCAL_PATH)/src/gfx \
	$(LOCAL_PATH)/src/input \
	$(LOCAL_PATH)/src/sfx

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/src/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/asset/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/exception/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gfx/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/input/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/sfx/*.cpp))

# no sdl mixer for now
LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES -fexceptions
LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid
LOCAL_STATIC_LIBRARIES := 
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf

include $(BUILD_SHARED_LIBRARY)