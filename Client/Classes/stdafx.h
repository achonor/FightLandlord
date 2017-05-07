#pragma once
#ifndef GGHEAD_H
#define GGHEAD_H

#include <exception>

#ifdef WIN32
#include "winsock2.h"
#endif
#include "stdio.h"
#include "cocos2d.h"
#include "net/MySocket.h"
#include "functions.h"
#include "Event/UserEvent.h"
#include "GameScene.h"



#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"
#include "proto/cmd.pb.h"

USING_NS_CC;

#endif