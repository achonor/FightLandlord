#!usr/bin/env python
#coding=utf-8

#服务类

import GGData
import functools
from proto import cmd_pb2

class Server(object):
    def __init__(self):
        self.waitQueue = []

    def readProto(func):
        @functools.wraps(func)
        def wrapper(self, playerID, className, requestProto):
            proto = className()
            proto.ParseFromString(requestProto.messageData.encode('utf-8'))
            # 打印协议内容
            print 'playerID: ', requestProto.playerID
            print 'MessageName: ', proto.__class__
            print  proto
            return func(self, playerID, proto)
        return wrapper

    #处理请求协议
    def requestServer(self,requestProto):

        className = None
        requestFunc = None
        messageName = requestProto.messageName
        if ('MessageLoginReq' == messageName):
            className = cmd_pb2.MessageLoginReq
            requestFunc= self.requestLogin
        elif('MessagePeopleReq' == messageName):
            className = cmd_pb2.MessagePeopleReq
            requestFunc = self.requestPeople
        elif('MessageStartGameReq' == messageName):
            className = cmd_pb2.MessageStartGameReq
            requestFunc = self.requestStartGame
        if(None == requestFunc):
            return
        #处理数据
        rProto = requestFunc(requestProto.playerID, className, requestProto)
        #发送数据
        GGData.My_Factory.returnData(requestProto.playerID, requestProto.messageID, rProto)

    #登陆请求
    @readProto
    def requestLogin(self, playerID, proto):
        rProto = cmd_pb2.MessageLoginRsp()
        rProto.playerID = playerID
        return rProto

    @readProto
    def requestPeople(self, playerID,  proto):
        rProto = cmd_pb2.MessagePeopleRsp()
        rProto.name = 'achonor'
        rProto.phone = '18075952730'
        rProto.age = 20
        return rProto

    @readProto
    def requestStartGame(self, playerID, proto):
        #玩家加入等待队列


        rProto = cmd_pb2.MessageStartGameRsp()
        return rProto