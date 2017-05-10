#!usr/bin/env python
#coding=utf-8

import copy
import time
import random
import GGData
import functions
from proto import cmd_pb2
from twisted.internet.defer import inlineCallbacks, Deferred

#叫地主等待时间
GRADLANDLORDTIME = 10

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
            self.playerList[i].poker = tmpList[i]
        #地主牌
        self.landlordPoker = tmpList[3]
        #地主的索引
        self.landlordIdx = -1
        #正在操作的玩家
        self.operatorIdx = -1
        #当前进行的状态(-1, 未开始, 1.抢地主, 2.打牌)
        self.gameState = -1
        #当前操作的剩结束
        self.operatorEndTme = 0
        #上一次出的牌
        self.lastOutPoker = []
        #把牌发给客户端
        for cPlayer in self.playerList:
            self.sendPoker(cPlayer)
            break

        # 3秒后开始游戏
        from twisted.internet import reactor
        reactor.callLater(3, self.gameLoop)

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
    #获取玩家当前状态
    def getPlayerState(self, cPlayer):
        rProto = cmd_pb2.MessageUpdateStateRsp()
        if(-1 == self.gameState):
            #游戏还没开始
            rProto.stateType = -1
        elif(1 == self.gameState):
            #抢地主状态
            rProto.stateType = 1
            rProto.playerIdx = self.operatorIdx
        else:
            #打牌状态
            rProto.stateType = 2
            rProto.landlordPoker = self.landlordPoker

        rProto.endTime = self.operatorEndTme
        rProto.midPoker = self.lastOutPoker
        return rProto


    def setMessageUpdateStateRsp(self, proto, waitTime, landlordPoker, selfPoker = []):
        proto.clear()
        proto.playerIdx = self.operatorIdx
        proto.stateType = self.gameState
        proto.endTime = time.time() + waitTime
        #保存结束时间
        self.operatorEndTme = proto.endTime
        for tmpPoker in self.lastOutPoker:
            tmpProto = proto.midPoker.add()
            tmpProto = copy.deepcopy(tmpPoker)
        for tmpPoker in landlordPoker:
            tmpProto = proto.landlordPoker.add()
            tmpProto = copy.deepcopy(tmpPoker)
        for tmpPoker in selfPoker:
            tmpProto = proto.selfPoker.add()
            tmpProto = copy.deepcopy(tmpPoker)
        return proto
    #返回b相对a的位置(0.自身 1.下家 2.上家）
    def getPlayerPos(self, a, b):
        return (b + 3 - a) % 3

    #游戏循环
    @inlineCallbacks
    def gameLoop(self):
        #同步状态的协议
        stateProto = cmd_pb2.MessageUpdateStateRsp()
        #标记开始抢地主
        self.gameState = 1
        #叫地主循环
        landlordIdx = random.randint(0, 2)
        for i in range(0, 4):
            #等待谁叫地主
            self.operatorIdx = (landlordIdx + i) % 3
            #通知三个玩家
            for k in range(0, 3):
                tmpPos = self.getPlayerPos(k, self.operatorIdx)
                stateProto = self.setMessageUpdateStateRsp(stateProto, GRADLANDLORDTIME, [])
                GGData.My_Factory.returnData(self.playerList[k], -1, stateProto)
                d = Deferred()

                res = yield d

    #游戏结束
    def gameOver(self):
        #恢复玩家状态
        for cPlayer in self.playerList:
            cPlayer.desk = None
            cPlayer.poker = []