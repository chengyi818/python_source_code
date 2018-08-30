/*
 * File Name: cydebug.h
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 28 Aug 2018 07:37:08 PM CST
 */
#include "Python.h"

#ifndef __CYDEBUG_H__
#define __CYDEBUG_H__

#ifdef __DEBUG__
#define DEBUG(format,...) printf(__FILE__ " | %05d | %s \n\t\t\t\t\t\t"format"\n", \
                                 __LINE__, __func__, ##__VA_ARGS__)
#define SHOW_MOD_NAME(content, mod) show_mod_name(content, mod)
#else
#define DEBUG(format,...)
#define SHOW_MOD_NAME(content, mod)
#endif

void show_mod_name(char* content, PyObject* mod) {
    if(mod == NULL) {
        return;
    } else if (mod == Py_None) {
        DEBUG("%s Py_None", content);
    } else {
        PyObject* tmp_name = PyObject_GetAttrString(mod, "__name__");
        char* tmp_string = PyString_AsString(tmp_name);
        DEBUG("%s %s", content, tmp_string);
    }
}

#endif /* __CYDEBUG_H__ */
