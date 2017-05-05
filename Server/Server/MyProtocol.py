#!usr/bin/env python
#coding=utf-8

import GGData
import functions
from twisted.python import log
from twisted.internet.protocol import Protocol, connectionDone


#协议类
class MyProtocol(Protocol):
    def __init__(self):
        #对应的玩家ID, 工厂类buildProtocol中赋值
        self.playerID = -1
        #工厂对象
        self.factory = None
        #当前正在接受的数据
        self.curData = ''
    def dataReceived(self, data):
        #print "dataReceived", data
        if (0 == len(self.curData)):
            self.curData = data
        else:
            self.curData += data
        if(len(self.curData) < GGData.LENGTH_HEAD):
            return
        dataLen = functions.charToInt(self.curData[0:4])
        if(dataLen + GGData.LENGTH_HEAD == len(self.curData) ):
            #这是一个完整的数据，交给工厂处理
            self.factory.dataReceived(self.playerID, self.curData[4:])
            self.curData = ''
        elif(dataLen + GGData.LENGTH_HEAD < len(self.curData)):
            #数据有多余（包含下一段数据）
            self.factory.dataReceived(self.playerID, self.curData[4:4 + dataLen])
            tmpData = self.curData[dataLen + 4:]
            self.curData = ''
            #递归处理
            self.dataReceived(tmpData)
        else:
            #数据没收完，不处理
            pass
    def connectionMade(self):
        print "connection success!!!", self.transport.getPeer()
    def connectionLost(self, reason=connectionDone):
        print "connection lost!!!", self.transport.getPeer()
        #通知工厂 断开连接
        self.factory.connectionLost(self.playerID)
    def sendData(self, data):
        #print "sendData: ", data
        self.transport.write(data)