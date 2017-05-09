#!usr/bin/env python
#coding=utf-8

#服务类

import player
import GGData
import gameDesk
import functools
from proto import cmd_pb2

class Server(object):
    def __init__(self):
        #玩家集合
        self.__playerDict = {}
        #等待队列
        self.__waitQueue = []
        #
        self.deskList = []

    def readProto(func):
        @functools.wraps(func)
        def wrapper(self, cPlayer, className, requestProto):
            proto = className()
            proto.ParseFromString(requestProto.messageData.encode('utf-8'))
            # 打印协议内容
            print 'playerID: ', requestProto.playerID
            print 'MessageName: ', proto.__class__
            print proto
            return func(self, cPlayer, proto)
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
        #玩家
        cPlayer = self.getPlayer(requestProto.playerID)
        #处理数据
        rProto = requestFunc(cPlayer, className, requestProto)
        #发送数据
        GGData.My_Factory.returnData(cPlayer, requestProto.messageID, rProto)

    #登陆请求
    @readProto
    def requestLogin(self, cPlayer, proto):
        rProto = cmd_pb2.MessageLoginRsp()
        rProto.playerID = cPlayer.playerID
        return rProto

    @readProto
    def requestPeople(self, cPlayer,  proto):
        rProto = cmd_pb2.MessagePeopleRsp()
        rProto.name = 'achonor'
        rProto.phone = '18075952730'
        rProto.age = 20
        return rProto

    @readProto
    def requestStartGame(self, cPlayer, proto):
        #玩家加入等待队列
        from twisted.internet import reactor
        reactor.callLater(0.1, self.addWaitQueue, cPlayer.playerID)

        rProto = cmd_pb2.MessageStartGameRsp()
        return rProto

    #讲玩家加入队列
    def addWaitQueue(self, playerID):
        self.__waitQueue.append(playerID)
        self.__waitQueue.append(playerID)
        self.__waitQueue.append(playerID)
        if (3 <= len(self.__waitQueue)):
            # 可以凑一桌了
            tmpDesk = gameDesk.desk(self.__waitQueue[0:3])
            self.deskList.append(tmpDesk)
            self.__waitQueue = self.__waitQueue[3:]

    #获取玩家
    def getPlayer(self, playerID):
        return self.__playerDict.get(playerID)
    #添加玩家
    def addPlayer(self, playerID, linkProto):
        cPlayer = player.Player(playerID, linkProto)
        self.__playerDict[playerID] = cPlayer
    #清除玩家
    def removePlayer(self, playerID):
        self.__playerDict.pop(playerID)
        #从等待队列移除
        if playerID in self.__waitQueue:
            self.__waitQueue.remove(playerID)