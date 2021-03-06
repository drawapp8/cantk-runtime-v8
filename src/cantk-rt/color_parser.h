/*
 * File     : color_parser.h
 * Brief    : color parser
 * Author   : Li XianJing <xianjimli@hotmail.com>
 * Web Site : http://www.tangide.com/
 *
 * Copyright (c) 2015 - 2015 Tangram HD.
 *
**/

#ifndef COLOR_PARSER_H
#define COLOR_PARSER_H

#include "console.h"

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

typedef struct _ColorRGBA {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}ColorRGBA;

ColorRGBA parseColor(const char* str);

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*COLOR_PARSER_H*/
