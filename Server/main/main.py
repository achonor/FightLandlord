#!usr/bin/env python
#coding=utf-8

from proto import cmd_pb2
from Server.MyProtocolFactory import MyServerFactory
from twisted.application import internet, service

port = 5010


def main():

    tmpPe= cmd_pb2.people()
    tmpPe.ID = 2017
    tmpPe.name = 'achonor'
    tmpStr = tmpPe.SerializeToString();
    '''
    tmpPe2 = cmd_pb2.people()
    tmpPe2.ParseFromString(tmpStr)
    print tmpPe2.ID, tmpPe2.name
    '''
    factory = MyServerFactory(tmpStr)

    from twisted.internet import reactor
    reactor.listenTCP(port, factory)

    print "start!!!"
    reactor.run()
    print "end!!!"
if ("__main__" == __name__):
    main()
