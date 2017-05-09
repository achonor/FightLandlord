#!usr/bin/env python
#coding=utf-8

import GGData
import functions
from proto import cmd_pb2


class desk:
    def __init__(self, playerIDList):
        self.poker = {}
        self.playerList = []
        for id in playerIDList:
            tmpPlayer = GGData.My_Server.getPlayer(id)
            self.playerList.append(tmpPlayer)
        #发牌
        tmpList = functions.randPoker()
        for i in range(0, 3, 1):
            self.playerList[i].poker = tmpList[i] + tmpList[3]
        #地主牌
        self.landlordPoker = tmpList[3]

        #把牌发给客户端
        for cPlayer in self.playerList:
            self.sendPoker(cPlayer)

    def sendPoker(self, cPlayer, messageID = -1):
        proto = cmd_pb2.MessageDealRsp()
        #上家的索引
        upIdx = (self.playerList.index(cPlayer) - 1 + 3) % 3
        proto.upNum = len(self.playerList[upIdx].poker)
        #下家的索引
        downIdx = (self.playerList.index(cPlayer) + 1) % 3
        proto.downNum = len(self.playerList[downIdx].poker)

        for tmpPoker in cPlayer.poker:
            tmpProto = proto.pokerList.add()
            colorNumber = functions.tearPoker(tmpPoker)
            tmpProto.color = colorNumber[0]
            tmpProto.number = colorNumber[1]
        GGData.My_Factory.returnData(cPlayer, messageID, proto)