#!usr/bin/env python
#coding=utf-8
import time
import copy
import random
import functools
from proto import cmd_pb2

poker = [516, 616, 13, 14, 15, 16, 17, 18, 19, 110, 111, 112, 113, 114, 115, 23, 24, 25, 26, 27, 28, 29, 210, 211, 212, 213, 214, 215, 33, 34, 35, 36, 37, 38, 39, 310, 311, 312, 313, 314, 315, 43, 44, 45, 46, 47, 48, 49, 410, 411, 412, 413, 414, 415]

#输出函数运行时间
def runtime(func):
    @functools.wraps(func)
    def wrapper():
        start = time.clock()
        func()
        end = time.clock()
        print "uesd time:", end - start
    return wrapper

#int转化成char
def intToChar(num):
    ret = ''
    for i in range(3, -1, -1):
        tmpInt = ((255 << (8 * i))) & num
        ret = ret + chr(tmpInt)
    return ret
#char转化成int
def charToInt(str):
    ret = 0
    for i in range(0, 4, 1):
        ret = (ret << 8) | ord(str[i])
    return ret
#封装协议
def serialization(proto, playerID = 0, messageID = 0):
    mainProto = cmd_pb2.MainProto()
    mainProto.playerID  = playerID
    mainProto.messageID = messageID
    mainProto.messageName = proto.__class__.__name__
    mainProto.messageData = proto.SerializeToString()
    mainProto.serverTime = time.time()
    #序列化包装后的协议
    tmpStr = mainProto.SerializeToString()
    tmpLen = len(tmpStr)
    tmpStr = intToChar(tmpLen) + tmpStr
    return tmpStr

#随机发牌
def randPoker():
    pokerNum = 54
    tmpPoker = copy.deepcopy(poker)
    retList = [[], [], []]
    for i in range(0, 17, 1):
        for k in range(0, 3, 1):
            tmpIdx = random.randint(0, pokerNum - 1)
            retList[k].append(tmpPoker[tmpIdx])
            pokerNum = pokerNum - 1
            tmpPoker.pop(tmpIdx)

    retList.append(tmpPoker)
    return retList

#拆分牌的花色和数字
def tearPoker(num):
    color = 0
    number = 0
    if(100 <= num):
        number = num % 100
        color = int(num / 100)
    else:
        number = num % 10
        color = int(num / 10)

    return [color, number]