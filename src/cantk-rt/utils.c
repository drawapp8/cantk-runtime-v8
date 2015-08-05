/*
 * File     : color_parser.c
 * Brief    : color parser
 * Author   : Li XianJing <xianjimli@hotmail.com>
 * Web Site : http://www.tangide.com/
 *
 * Copyright (c) 2015 - 2015 Tangram HD.
 *
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>    
#include <unistd.h>
#include "utils.h"

int atoi_r(const char* str, const char* start) {
	int i = 0;
	int value = 0;
	const char* p = str;

	while(p >= start) {
		char c = *p;
		if(c >= '0' && c <= '9') {
			c = c - '0';
			value = value + (i ? (i * 10 * c) :  c );
		}
		else {
			break;
		}
		i++;
		p--;
	}

	return value;
}

int parseFontSize(const char* str) 
{
	int fontSize = 12;
	const char* px = NULL;
	const char* pt = NULL;

	if(str) {
		px = strstr(str, "px");
		pt = strstr(str, "pt");
		if(px) {
			fontSize = atoi_r(px-1, str);
		}
		else if(pt) {
			fontSize = atoi_r(pt-1, str) * 1.5;
		}
	}

	return fontSize;
}

int now() {
	struct timeval tv = {0};
	struct timezone tz = {0};

	gettimeofday (&tv, NULL);

	int value = (tv.tv_sec & 0xffff) * 1000 + tv.tv_usec/1000;

	return value;
}
