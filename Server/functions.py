#!usr/bin/env python
#coding=utf-8
import time
import functools
from proto import cmd_pb2

def runtime(func):
    @functools.wraps(func)
    def wrapper():
        start = time.clock()
        func()
        end = time.clock()
        print "uesd time:", end - start
    return wrapper


def intToChar(num):
    ret = ''
    for i in range(3, -1, -1):
        tmpInt = ((255 << (8 * i))) & num
        ret = ret + chr(tmpInt)
    return ret
def charToInt(str):
    ret = 0
    for i in range(0, 4, 1):
        ret = (ret << 8) | ord(str[i])
    return ret

def serialization(proto, playerID = 0, messageID = 0):
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
