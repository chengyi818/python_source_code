#!/usr/bin/env python2
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 15 Jun 2018 05:10:24 PM CST

import argparse

parser = argparse.ArgumentParser(description='Python Source Code Dis Tool')
parser.add_argument('-f', '--file',
                    type=str,
                    help='Specify file to dis',
                    dest='file')

args = parser.parse_known_args()

file_name = args[0].file
s = open(file_name).read()
co = compile(s, file_name, 'exec')
import dis
dis.dis(co)
