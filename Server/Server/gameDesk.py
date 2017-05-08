#!usr/bin/env python
#coding=utf-8

import GGData
import functions
from proto import cmd_pb2


class desk:
    def __init__(self, playerList):
        self.poker = {}
        self.playerList = playerList
        #发牌
        tmpList = functions.randPoker()
        for i in range(0, 3, 1):
            self.poker[self.playerList[i]] = tmpList[i]
        #地主牌
        self.landlordPoker = tmpList[3]

        #把牌发给客户端
        for playerID in self.playerList:
            self.sendPoker(playerID)

    def sendPoker(self, playerID, messageID = -1):
        proto = cmd_pb2.MessageDealRsp()
        #上家的索引
        upIdx = (self.playerList.index(playerID) - 1 + 3) % 3
        proto.upNum = len(self.poker[self.playerList[upIdx]])
        #下家的索引
        downIdx = (self.playerList.index(playerID) + 1) % 3
        proto.downNum = len(self.poker[self.playerList[downIdx]])

        for tmpPoker in self.poker[playerID]:
            tmpProto = proto.pokerList.add()
            colorNumber = functions.tearPoker(tmpPoker)
            tmpProto.color = colorNumber[0]
            tmpProto.number = colorNumber[1]
        GGData.My_Factory.returnData(playerID, messageID, proto)