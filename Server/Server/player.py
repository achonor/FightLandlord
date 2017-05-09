#!usr/bin/env python
#coding=utf-8


'''玩家的信息'''

class Player(object):
    def __init__(self, playerID, linkProto):
        #玩家ID
        self.__playerID = playerID
        #和玩家的链接
        self.__linkProto = linkProto
        #玩家所在的牌桌
        self.__desk = None
        #玩家的牌
        self.__poker = []

    @property
    def playerID(self):
        return self.__playerID

    @property
    def linkProto(self):
        return self.__linkProto
    @linkProto.setter
    def linkProto(self, value):
        self.__linkProto = value

    @property
    def desk(self):
        return self.__desk

    @desk.setter
    def desk(self, value):
        self.__desk = value

    @property
    def poker(self):
        return self.__poker
    @poker.setter
    def poker(self, pokerList):
        self.__poker = pokerList






