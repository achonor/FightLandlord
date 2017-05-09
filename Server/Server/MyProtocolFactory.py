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
        #添加玩家
        GGData.My_Server.addPlayer(tmpProto.playerID, tmpProto)
        return tmpProto

    def dataReceived(self, playerID, data):
        #解析协议
        mainProto = cmd_pb2.MainProto()
        mainProto.ParseFromString(data)
        mainProto.playerID = playerID
        #交给服务类处理
        GGData.My_Server.requestServer(mainProto)

    #返回数据给客户端
    def returnData(self, cPlayer, messageID, proto):
        #序列化协议
        rspData = functions.serialization(proto, cPlayer.playerID, messageID)
        #发送数据
        cPlayer.linkProto.sendData(rspData)

    def connectionLost(self, playerID):
        #移除
        self.removePlayer(playerID)

    def removePlayer(self, playerID):
        #移除连接
        self.linkProto.pop(playerID)
        #移除玩家
        GGData.My_Server.removePlayer(playerID)