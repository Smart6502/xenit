#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

enum dlog_status
{
	info,
	ok,
	warn,
	fail,
	fatal,
};


void mount_fss();
void dlog_sym(int);
int run(char*, ...);
void delay(int);

extern sigset_t set;

#define dlog(level, msg, ...) dlog_sym(level); printf((msg), ##__VA_ARGS__); putchar('\n')
#define fatalfunc(fname, rcode) dlog(fatal, "%s() failed with error %ld, errno %d (%s).", name, (long int)rcode, errno, strerror(errno))

#endif
