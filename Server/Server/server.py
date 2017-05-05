#!usr/bin/env python
#coding=utf-8

#服务类

import GGData
from proto import cmd_pb2

class Server(object):
    def __init__(self):
        pass

    #处理请求协议
    def requestServer(self, playerID, messageID, requestProto):
        protoType = type(requestProto)
        if (cmd_pb2.MessageLoginReq == protoType):
            self.requestLogin(playerID, messageID, requestProto)
        elif():
            pass

    #登陆请求
    def requestLogin(self,playerID, messageID,  proto):
        rProto = cmd_pb2.MessageLoginRsp()
        rProto.playerID = playerID
        GGData.My_Factory.returnData( playerID , messageID, rProto)