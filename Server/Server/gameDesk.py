#!usr/bin/env python
#coding=utf-8

import copy
import time
import random
import GGData
import functions
from proto import cmd_pb2
from twisted.internet import defer
from twisted.internet.defer import inlineCallbacks, Deferred

#叫地主等待时间
GRADLANDLORDTIME = 10
#出牌等待时间
OUTPOKERTIME= 25


class desk:
    def __init__(self, playerIDList):
        #玩家列表
        self.playerList = []
        #地主牌
        self.landlordPoker = []
        #地主牌
        #地主的索引
        self.landlordIdx = -1
        #正在操作的玩家
        self.operatorIdx = -1
        #当前进行的状态(0, 未开始, 1.抢地主, 2.打牌)
        self.gameState = 0
        #当前操作的剩结束
        self.operatorEndTme = 0
        #上一次出的牌
        self.lastOutPoker = []
        #等待触发的Deferred
        self.waitDeferred = None
        #初始化角色
        for id in playerIDList:
            tmpPlayer = GGData.My_Server.getPlayer(id)
            tmpPlayer.desk = self
            self.playerList.append(tmpPlayer)


    #游戏开始
    @inlineCallbacks
    def startGame(self):
        while(True):
            # 随机生成牌
            self.randomDeal()
            # 3秒后开始游戏
            d = Deferred()
            from twisted.internet import reactor
            reactor.callLater(3, d.callback, 1)
            yield d
            d = self.gameLoop()
            ret = yield d
            if(True == ret):
                #游戏结束
                self.gameOver()
                break
    #给三个玩家发牌
    def randomDeal(self):
        #发牌
        tmpList = functions.randPoker()
        for i in range(0, 4, 1):
            tmpPokerList = self.landlordPoker
            if(i <= 2):
                self.playerList[i].poker = []
                tmpPokerList = self.playerList[i].poker
            for tmp in tmpList[i]:
                colorNumber = functions.tearPoker(tmp)
                tmpProto = cmd_pb2.MessageDataPoker()
                tmpProto.color = colorNumber[0]
                tmpProto.number = colorNumber[1]
                tmpPokerList.append(tmpProto)
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
            tmpProto.color = tmpPoker.color
            tmpProto.number = tmpPoker.number
        GGData.My_Factory.returnData(cPlayer, messageID, proto)
    #获取玩家当前状态
    def getPlayerState(self, cPlayer):
        rProto = cmd_pb2.MessageUpdateStateRsp()
        #玩家自己的牌
        for tmpPoker in cPlayer.poker:
            tmpProto = rProto.selfPoker.add()
            tmpProto.color = tmpPoker.color
            tmpProto.number = tmpPoker.number
        #其它两个玩家的手牌数量
        tmpSelfIdx = self.playerList.index(cPlayer)
        rProto.upPokerNum = len(self.playerList[(tmpSelfIdx + 3 - 1) % 3].poker)
        rProto.downPokerNum = len(self.playerList[(tmpSelfIdx + 1) % 3].poker)
        if(0 == self.gameState):
            #游戏还没开始
            rProto.stateType = 0
            return rProto
        elif(1 == self.gameState):
            #抢地主状态
            rProto.stateType = 1
            rProto.playerIdx = self.getPlayerPos(tmpSelfIdx, self.operatorIdx)
        else:
            #打牌状态
            rProto.stateType = 2
            #同步地主牌
            for tmpPoker in self.landlordPoker:
                tmpProto = rProto.landlordPoker.add()
                tmpProto.color = tmpPoker.color
                tmpProto.number = tmpPoker.number
            #上一次出的牌
            for tmpPoker in self.lastOutPoker:
                tmpProto = rProto.midPoker.add()
                tmpProto.color = tmpPoker.color
                tmpProto.number = tmpPoker.number
        rProto.laveTime = int(self.operatorEndTme - functions.getSystemTime())
        if(rProto.laveTime < 0):
            rProto.laveTime = 0
        return rProto
    def updataAllPlayerState(self, outTime, lastOperatorPlayerIdx):
        for i in range(0, 3):
            stateProto = cmd_pb2.MessageUpdateStateRsp()
            tmpPos = self.getPlayerPos(i, self.operatorIdx)
            tmpSelfPoker = []
            tmpLandlordPoker = []
            if(2 == self.gameState):
                tmpLandlordPoker = self.landlordPoker
                if(i == lastOperatorPlayerIdx):
                    tmpSelfPoker = self.playerList[i].poker
            stateProto = self.setMessageUpdateStateRsp(stateProto, tmpPos, outTime, tmpLandlordPoker, tmpSelfPoker)
            GGData.My_Factory.returnData(self.playerList[i], -1, stateProto)

    def setMessageUpdateStateRsp(self, proto, operatorPos, waitTime, landlordPoker, selfPoker = []):
        proto.playerIdx = operatorPos
        proto.stateType = self.gameState
        proto.laveTime = waitTime #functions.getSystemTime() + waitTime
        #保存结束时间
        self.operatorEndTme = proto.laveTime + functions.getSystemTime()
        for tmpPoker in self.lastOutPoker:
            tmpProto = proto.midPoker.add()
            tmpProto.color = tmpPoker.color
            tmpProto.number = tmpPoker.number
        for tmpPoker in landlordPoker:
            tmpProto = proto.landlordPoker.add()
            tmpProto.color = tmpPoker.color
            tmpProto.number = tmpPoker.number
        for tmpPoker in selfPoker:
            tmpProto = proto.selfPoker.add()
            tmpProto.color = tmpPoker.color
            tmpProto.number = tmpPoker.number
        return proto
    #返回b相对a的位置(0.自身 1.下家 2.上家）
    def getPlayerPos(self, a, b):
        return (b + 3 - a) % 3

    #游戏循环
    @inlineCallbacks
    def gameLoop(self):
        #标记开始抢地主
        self.gameState = 1
        #叫地主循环
        landlordIdx = random.randint(0, 2)
        #最后叫地主的人
        lastGradIdx = -1
        for i in range(0, 4):
            #等待谁叫地主
            self.operatorIdx = (landlordIdx + i) % 3
            if(3 == i and self.operatorIdx == lastGradIdx):
                break
            #通知三个玩家
            self.updataAllPlayerState(GRADLANDLORDTIME, -1)
            d = Deferred()
            self.registerEvent(self.operatorIdx, d, GRADLANDLORDTIME)
            ret = yield d
            if(True == ret):
                lastGradIdx = self.operatorIdx
        if(-1 == lastGradIdx):
            #没人抢地主，重新开始
            defer.returnValue(False)
        #设置地主
        self.landlordIdx = lastGradIdx
        self.playerList[self.landlordIdx].poker.extend(self.landlordPoker)
        #标记开始打牌
        self.gameState = 2
        #地主开始操作
        self.operatorIdx = lastGradIdx
        #同步状态
        self.updataAllPlayerState(GRADLANDLORDTIME, lastGradIdx)


    #注册等待事件(等待
    def registerEvent(self, playerIdx, defe, outTime):
        def tmpFunc(value):
            if(self.waitDeferred == defe):
                defe.callback(value)

        self.waitDeferred = defe
        self.operatorIdx = playerIdx
        #超时自动触发
        from twisted.internet import reactor
        reactor.callLater(outTime, tmpFunc, None)
    #处理抢地主
    def handleGradLandlord(self, playerID , proto):
        if(playerID != self.playerList[self.operatorIdx].playerID):
            #等待的不是该玩家的请求
            return
        tmpDeferred, self.waitDeferred = self.waitDeferred , None
        tmpDeferred.callback(proto.isGrad)

    #游戏结束
    def gameOver(self):
        #恢复玩家状态
        for cPlayer in self.playerList:
            cPlayer.desk = None
            cPlayer.poker = []