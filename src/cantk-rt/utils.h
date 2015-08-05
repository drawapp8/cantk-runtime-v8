/*
 * File     : color_parser.h
 * Brief    : color parser
 * Author   : Li XianJing <xianjimli@hotmail.com>
 * Web Site : http://www.tangide.com/
 *
 * Copyright (c) 2015 - 2015 Tangram HD.
 *
**/

#ifndef UTILS_H
#define UTILS_H

#include "console.h"

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

int now();
int atoi_r(const char* str, const char* start);
int parseFontSize(const char* str);

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*UTILS_H*/
