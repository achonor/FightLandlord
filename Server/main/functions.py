#!usr/bin/env python
#coding=utf-8
import time
from proto import cmd_pb2

def intToChar(num):
    ret = ''
    for i in range(3, -1, -1):
        tmpInt = ((255 << (8 * i))) & num
        ret = ret + chr(tmpInt)
    return ret

def serialization(proto, playerID, messageID):
    mainProto = cmd_pb2.MainProto()
    mainProto.playerID  = playerID
    mainProto.messageID = messageID
    mainProto.messageName = proto.__class__.__name__
    mainProto.messageData = proto.SerializeToString()
    mainProto.serverTime = int(time.time())
    #序列化包装后的协议
    tmpStr = mainProto.SerializeToString()
    tmpLen = len(tmpStr)
    tmpStr = intToChar(tmpLen) + tmpStr
    return tmpStr
