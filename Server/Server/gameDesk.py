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
        #上一个操作者是否抢地主(0.没有上家，1.抢了， 2.没抢)
        self.lastIsGrad = 0
        #上一个操作者是否出牌（0.没有上家，1.出了，没出)
        self.lastIsOut = 0
        #上一个出牌的玩家索引
        self.lastOutPokerIdx = -1
        #等待触发的Deferred
        self.waitDeferred = None
        #初始化角色
        for id in playerIDList:
            tmpPlayer = GGData.My_Server.getPlayer(id)
            tmpPlayer.desk = self
            self.playerList.append(tmpPlayer)


    def initData(self):
        # 地主的索引
        self.landlordIdx = -1
        # 正在操作的玩家
        self.operatorIdx = -1
        # 当前进行的状态(0, 未开始, 1.抢地主, 2.打牌)
        self.gameState = 0
        # 当前操作的剩结束
        self.operatorEndTme = 0
        # 上一次出的牌
        self.lastOutPoker = []
        # 上一个操作者是否抢地主(0.没有上家，1.抢了， 2.没抢)
        self.lastIsGrad = 0
        # 上一个操作者是否出牌（0.没有上家，1.出了，没出)
        self.lastIsOut = 0
        #上一个出牌的玩家索引
        self.lastOutPokerIdx = -1
        # 等待触发的Deferred
        self.waitDeferred = None

    #游戏开始
    @inlineCallbacks
    def startGame(self):
        while(True):
            #初始化数据
            self.initData()
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
        self.landlordPoker = []
        tmpList = functions.randPoker()
        for i in range(0, 4, 1):
            # 默认给地主牌赋值
            tmpPokerList = self.landlordPoker
            if(i <= 2):
                #小于三就给玩家牌赋值
                self.getPlayerByIdx(i).poker = []
                tmpPokerList = self.getPlayerByIdx(i).poker
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
        upIdx = (self.getPlayerIdx(cPlayer) - 1 + 3) % 3
        proto.upNum = len(self.getPlayerByIdx(upIdx).poker)
        #下家的索引
        downIdx = (self.getPlayerIdx(cPlayer) + 1) % 3
        proto.downNum = len(self.getPlayerByIdx(downIdx).poker)

        for tmpPoker in cPlayer.poker:
            tmpProto = proto.pokerList.add()
            tmpProto.color = tmpPoker.color
            tmpProto.number = tmpPoker.number
        GGData.My_Factory.returnData(cPlayer, messageID, proto)
    #获取玩家当前状态
    def getPlayerState(self, cPlayer):
        rProto = cmd_pb2.MessageUpdateStateRsp()
        #上一个操作者是否抢地主
        rProto.lastIsGrad = self.lastIsGrad
        #上一个操作者是否出牌
        rProto.lastIsOut = self.lastIsOut
        if(-1 != self.landlordIdx):
            #有地主，同步地主相对自己的位置
            tmpIdx = self.getPlayerIdx(cPlayer)
            rProto.landlordIdx  = self.getPlayerPos(tmpIdx, self.landlordIdx)
        #玩家自己的牌
        for tmpPoker in cPlayer.poker:
            tmpProto = rProto.selfPoker.add()
            tmpProto.color = tmpPoker.color
            tmpProto.number = tmpPoker.number
        #其它两个玩家的手牌数量
        tmpSelfIdx = self.getPlayerIdx(cPlayer)
        rProto.upPokerNum = len(self.getPlayerByIdx((tmpSelfIdx + 3 - 1) % 3).poker)
        rProto.downPokerNum = len(self.getPlayerByIdx((tmpSelfIdx + 1) % 3).poker)
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
            #地主相对当前玩家的位置
            tmpLandlordPos = 0
            #玩家自己的牌
            tmpSelfPoker = []
            #地主牌
            tmpLandlordPoker = []
            if(2 == self.gameState):
                tmpLandlordPos = self.getPlayerPos(i, self.landlordIdx)
                tmpLandlordPoker = self.landlordPoker
                if(i == lastOperatorPlayerIdx):
                    tmpSelfPoker = self.getPlayerByIdx(i).poker
            stateProto = self.setMessageUpdateStateRsp(stateProto, tmpPos, outTime, tmpLandlordPoker, tmpLandlordPos, tmpSelfPoker)
            GGData.My_Factory.returnData(self.getPlayerByIdx(i), -1, stateProto)

    def setMessageUpdateStateRsp(self, proto, operatorPos, waitTime, landlordPoker, landlordPos, selfPoker):
        proto.playerIdx = operatorPos
        #当前游戏状态
        proto.stateType = self.gameState
        #等待玩家响应的时间
        proto.laveTime = waitTime #functions.getSystemTime() + waitTime
        # 上一个操作者是否抢地主
        proto.lastIsGrad = self.lastIsGrad
        ##上一个操作者是否出牌
        proto.lastIsOut = self.lastIsOut
        #同步地主相对自己的位置
        proto.landlordIdx  = landlordPos
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
    #获取玩家
    def getPlayerByIdx(self, idx):
        return self.playerList[idx]
    #获取玩家索引
    def getPlayerIdx(self, cPlayer):
        return self.playerList.index(cPlayer)
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
            self.registerEvent(self.operatorIdx, d, GRADLANDLORDTIME, False)
            ret = yield d
            self.lastIsGrad = ret
            if(True == ret):
                self.lastIsGrad = 1
                lastGradIdx = self.operatorIdx
            else:
                self.lastIsGrad = 2
        if(-1 == lastGradIdx):
            #没人抢地主，重新开始
            defer.returnValue(False)
        #过了抢地主的状态
        self.lastIsGrad = 0
        #设置地主
        self.landlordIdx = lastGradIdx
        self.getPlayerByIdx(self.landlordIdx).poker.extend(self.landlordPoker)
        #标记开始打牌
        self.gameState = 2
        #地主开始操作
        self.operatorIdx = lastGradIdx
        #上一个操作者
        lastOperatorIdx = self.operatorIdx
        #出牌循环
        while(True):
            if(self.lastOutPokerIdx == self.operatorIdx):
                #没人要的起
                self.lastOutPoker = []
            # 同步状态
            self.updataAllPlayerState(OUTPOKERTIME, lastOperatorIdx)
            #等待出牌
            d = Deferred()
            self.registerEvent(self.operatorIdx, d, OUTPOKERTIME, [])
            ret = yield d
            if(0 < len(ret)):
                #出牌了
                self.lastIsOut = 1
                self.lastOutPoker = ret
                self.lastOutPokerIdx = self.operatorIdx
                pokerList = self.getPlayerByIdx(self.operatorIdx).poker
                for tmpPoker in ret:
                    #从手牌移除
                    pokerList.remove(tmpPoker)
                if(len(pokerList) <= 0):
                    #出完了
                    self.gameOver(self.operatorIdx)
                    break
            else:
                self.lastIsOut = 2 #没出
            lastOperatorIdx, self.operatorIdx = self.operatorIdx, (self.operatorIdx + 1) % 3  # 修改操作者
        defer.returnValue(True)

    #注册等待事件(等待
    def registerEvent(self, playerIdx, defe, outTime, outTimeValue):
        def tmpFunc(value):
            if(self.waitDeferred == defe):
                defe.callback(value)

        self.waitDeferred = defe
        self.operatorIdx = playerIdx
        #超时自动触发
        from twisted.internet import reactor
        reactor.callLater(outTime, tmpFunc, outTimeValue)
    #处理抢地主
    def handleGradLandlord(self, playerID , proto):
        if(playerID != self.getPlayerByIdx(self.operatorIdx).playerID):
            #等待的不是该玩家的请求
            return
        tmpDeferred, self.waitDeferred = self.waitDeferred , None
        tmpDeferred.callback(proto.isGrad)

    #处理出牌事件
    def handleOutPoker(self, playerID, proto):
        if (playerID != self.getPlayerByIdx(self.operatorIdx).playerID):
            # 等待的不是该玩家的请求
            return
        tmpDeferred, self.waitDeferred = self.waitDeferred, None
        tmpDeferred.callback(proto.poker)
    #游戏结束
    def gameOver(self, winningIdx):
        #是否是地主获胜
        isLandlord = (winningIdx == self.landlordIdx)
        #恢复玩家状态
        for tmpIdx in range(0, 3):
            cPlayer = self.playerList[tmpIdx]
            cPlayer.desk = None
            cPlayer.poker = []
            rProto = cmd_pb2.MessageGameResultRsp()
            if(True == isLandlord):
                #如果是地主获胜,那么就只有地主获胜
                rProto.isWinning  = (tmpIdx == self.landlordIdx)
            else:
                #农民获胜，那么只有地主输
                rProto.isWinning = (tmpIdx != self.landlordIdx)
            #同步结果
            GGData.My_Factory.returnData(cPlayer, -1, rProto)