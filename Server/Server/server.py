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
        requestFunc = None
        protoType = type(requestProto)
        if (cmd_pb2.MessageLoginReq == protoType):
            requestFunc= self.requestLogin
        elif(cmd_pb2.MessagePeopleReq == protoType):
            requestFunc = self.requestPeople
        if(None == requestFunc):
            return
        #处理数据
        rProto = requestFunc(playerID, messageID, requestProto)
        #发送数据
        GGData.My_Factory.returnData(playerID, messageID, rProto)

    #登陆请求
    def requestLogin(self, playerID, messageID,  proto):
        rProto = cmd_pb2.MessageLoginRsp()
        rProto.playerID = playerID
        return rProto

    def requestPeople(self, playerID, messageID,  proto):
        rProto = cmd_pb2.MessagePeopleRsp()
        rProto.name = 'achonor'
        rProto.phone = '18075952730'
        rProto.age = 20
        return rProto