#!usr/bin/env python
#coding=utf-8

from MyProtocol import MyProtocol
from twisted.internet.protocol import  ServerFactory

class MyServerFactory(ServerFactory):
    protocol = MyProtocol
    def __init__(self, data):
        self.data = data
    def buildProtocol(self, addr):
        tmpProto = ServerFactory.buildProtocol(self, addr)
        tmpProto.factory = self
        return tmpProto
    def received(self, data):
        pass
    def getData(self):
        return self.data