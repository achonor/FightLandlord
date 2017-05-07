#!usr/bin/env python
#coding=utf-

import sys
sys.path.append('..')

import time
import GGData
from proto import cmd_pb2
import functions
from Server.MyProtocolFactory import MyServerFactory
from twisted.application import internet, service

port = 5010


def main():
    #初始化公共数据
    GGData.My_InitGGData()

    from twisted.internet import reactor
    reactor.listenTCP(port, GGData.My_Factory)

    print "start!!!"
    reactor.run()
    print "end!!!"

if ("__main__" == __name__):
    main()
