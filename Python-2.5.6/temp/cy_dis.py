#!/usr/bin/env python2
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 15 Jun 2018 05:10:24 PM CST

import argparse
import dis

def is_code_object(code_object):
    if type(code_object).__name__ == 'code':
        return True

    return False

def show_code_object(code_object):
    if not is_code_object(code_object):
        return

    for tmp in code_object.co_consts:
        if is_code_object(tmp):
            show_code_object(tmp)

    print(code_object.co_name)
    dis.dis(code_object)
    print("---------------------------")



parser = argparse.ArgumentParser(description='Python Source Code Dis Tool')
parser.add_argument('-f', '--file',
                    type=str,
                    help='Specify file to dis',
                    dest='file')

args = parser.parse_known_args()

file_name = args[0].file
s = open(file_name).read()
co = compile(s, file_name, 'exec')

show_code_object(co)
