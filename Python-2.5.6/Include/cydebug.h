/*
 * File Name: cydebug.h
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 28 Aug 2018 07:37:08 PM CST
 */

#ifndef __CYDEBUG_H__
#define __CYDEBUG_H__

#ifdef __DEBUG__
#define DEBUG(format,...) printf(__FILE__ " | %05d | %s \n\t\t\t\t\t\t"format"\n", \
                                 __LINE__, __func__, ##__VA_ARGS__)
#else
#define DEBUG(format,...)
#endif


#endif /* __CYDEBUG_H__ */
