LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := protobuf_static
LOCAL_MODULE_FILENAME := libprotobuf
LOCAL_SRC_FILES := ../libprotobuf.a
LOCAL_C_INCLUDES := ../
include $(PREBUILT_STATIC_LIBRARY) 

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

 

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/GGText.cpp \
                   ../../Classes/GGData.cpp \
                   ../../Classes/functions.cpp \
                   ../../Classes/stdafx.cpp \
                   ../../Classes/Event/UserEvent.cpp \
                   ../../Classes/net/Client.cpp \
                   ../../Classes/net/MySocket.cpp \
                   ../../Classes/net/Request.cpp \
                   ../../Classes/game/UIPoker.cpp \
                   ../../Classes/game/UIPlayGame.cpp \
                   ../../Classes/game/MyGme.cpp \
                   ../../Classes/game/UIStartGame.cpp \
                   ../../Classes/game/ScreenLayer.cpp \
                   ../../Classes/game/UIPanel.cpp \
                   ../../Classes/proto/cmd.pb.cc \
                   ../../Classes/controls/UIMessageBox.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					D:/protobuf/src2.6.1

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END



LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += protobuf_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
