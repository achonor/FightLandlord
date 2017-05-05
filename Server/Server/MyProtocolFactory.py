#!usr/bin/env python
#coding=utf-8

import GGData
import functions
from proto import cmd_pb2
from MyProtocol import MyProtocol
from twisted.internet.protocol import  ServerFactory

class MyServerFactory(ServerFactory):
    protocol = MyProtocol
    def __init__(self):
        #玩家分配唯一ID
        self.playerIDIdx = 1
        #保存所有链接
        self.linkProto = {}

    def buildProtocol(self, addr):
        tmpProto = ServerFactory.buildProtocol(self, addr)
        #分配ID
        tmpProto.playerID = self.playerIDIdx
        self.playerIDIdx += 1
        #保存连接
        self.linkProto[tmpProto.playerID] = tmpProto
        return tmpProto

    def dataReceived(self, playerID, data):
        #解析协议
        mainProto = cmd_pb2.MainProto()
        mainProto.ParseFromString(data)
        mainProto.playerID = playerID

        proto = eval('cmd_pb2.' + mainProto.messageName + '()')
        proto.ParseFromString(mainProto.messageData.encode('utf-8'))
        #打印协议内容
        print proto.__class__,": "
        print proto
        #交给服务类处理
        GGData.My_Server.requestServer(mainProto.playerID, mainProto.messageID, proto)

    #返回数据给客户端
    def returnData(self, playerID, messageID, proto):
        #获取连接
        linkProto = self.getLinkProto(playerID)
        #序列化协议
        rspData = functions.serialization(proto, playerID, messageID)
        #发送数据
        linkProto.sendData(rspData)

    def getLinkProto(self, playerID):
        return self.linkProto.get(playerID)

    def connectionLost(self, playerID):
        self.linkProto.pop(playerID)