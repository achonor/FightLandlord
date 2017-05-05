#!usr/bin/env python
#coding=utf-8

#保存公共数据
import functions
from Server import server
from Server.MyProtocolFactory import MyServerFactory

#包头长度
global LENGTH_HEAD
LENGTH_HEAD = 4

#全局的连接工厂
global My_Factory
#全局服务类
global My_Server

def My_InitGGData():
    global My_Factory
    global My_Server

    My_Factory = MyServerFactory()
    My_Server  = server.Server()

