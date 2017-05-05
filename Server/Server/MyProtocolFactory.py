#!usr/bin/env python
#coding=utf-8

import functions
from proto import cmd_pb2
from MyProtocol import MyProtocol
from twisted.internet.protocol import  ServerFactory

class MyServerFactory(ServerFactory):
    protocol = MyProtocol
    def __init__(self):
        #玩家分配唯一ID
        self.playerIDIdx = 0
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

    def dataReceived(self, data):
        #解析协议
        mainProto = cmd_pb2.MainProto()
        mainProto.ParseFromString(data)

        proto = eval('cmd_pb2.' + mainProto.messageName + '()')
        proto.ParseFromString(mainProto.messageData.encode('utf-8'))
        print proto
        #测试协议返回
        def testReturn():
            proto = eval('cmd_pb2.' + mainProto.messageName[0:-3] + 'Rsp()')
            proto.name = 'achonor'
            proto.phone = '18075952730'
            proto.age = 20
            rspData = functions.serialization(proto, mainProto.playerID, mainProto.messageID)
            linkProto = self.getLinkProto(mainProto.playerID)
            linkProto.sendData(rspData)
        
        from twisted.internet import reactor
        reactor.callLater(0.1, testReturn)
        reactor.callLater(0.1, testReturn)

    def getLinkProto(self, playerID):
        return self.linkProto.get(playerID)

    def connectionLost(self, playerID):
        self.linkProto.pop(playerID)
