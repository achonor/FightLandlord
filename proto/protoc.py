#!usr/bin/env python
#coding=utf-8

import os

OUT_PATH_CPP = '../Client/Classes/proto'
OUT_PATH_PYTHON = '../Server/proto'
BASE_CMD = 'protoc -I=. --cpp_out=%s --python_out=%s'%(OUT_PATH_CPP, OUT_PATH_PYTHON)

def protoc():
    fileList = [x for x in os.listdir('.') if os.path.isfile(x) and os.path.splitext(x)[1]=='.proto']
    for fileName in fileList:
        cmd  = BASE_CMD + ' ' + fileName
        os.system(cmd)
        print cmd

if('__main__' == __name__):
    protoc()