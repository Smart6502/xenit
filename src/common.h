#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>

enum dlog_status
{
	fail,
	fatal,
	ok,
	warn,
	info,
};

void dlog_sym(int level);
#define dlog(level, msg, ...) dlog_sym(level); printf((msg), ##__VA_ARGS__); putchar('\n');

#endif
