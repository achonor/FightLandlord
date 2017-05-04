#!usr/bin/env python
#coding=utf-8

from twisted.python import log
from twisted.internet.protocol import Protocol, connectionDone
#协议类
class MyProtocol(Protocol):
    def __init__(self):
        pass
    def dataReceived(self, data):
        log.msg("dataReceived", data)
        #工厂类处理
        self.factory.received(data)
    def connectionMade(self):
        print "connection success!!!", self.transport.getPeer()
        tmpData = self.factory.getData()
        from twisted.internet import reactor
        reactor.callLater(1, self.sendData, tmpData)
        reactor.callLater(2, self.sendData, tmpData)

    def connectionLost(self, reason=connectionDone):
        log.msg("connection lost!!!")

    def sendData(self, data):
        print "sendData: ", data
        self.transport.write(data)