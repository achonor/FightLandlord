#!usr/bin/env python
#coding=utf-8

import os
import copy


def main():
    fileList = [x for x in os.listdir('.') if os.path.isfile(x) and os.path.splitext(x)[1] == '.png']
    for fileName in fileList:
        oldFileName = copy.deepcopy(fileName)
        fileName = fileName.replace("A", "1")
        fileName = fileName.replace("J", "11")
        fileName = fileName.replace("Q", "12")
        fileName = fileName.replace("K", "13")
        fileName = fileName.replace("\xba\xda\xcc\xd2", "_1_")
        fileName = fileName.replace("\xba\xec\xd0\xc4", "_2_")
        fileName = fileName.replace("\xc3\xb7\xbb\xa8", "_3_")
        fileName = fileName.replace("\xb7\xbd\xbf\xe9", "_4_")
        print oldFileName,'->',fileName
        os.rename(oldFileName, 'poker' + fileName)
if('__main__' == __name__):
    main()