#!usr/bin/env python
#coding=utf-8

#保存公共数据
import functions
from Server.MyProtocolFactory import MyServerFactory

#全局的连接工厂
global My_Factory

def My_InitGGData():
    global My_Factory
    My_Factory = MyServerFactory()


