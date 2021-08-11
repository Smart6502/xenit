#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>

enum dlog_status
{
	success,
	fail,
	info,
};

void dlog_sym(int level);
#define dlog(level, msg, ...) dlog_sym(level); printf((msg), ##__VA_ARGS__)

#endif
