#ifndef COMMON_H
#define COMMON_H

enum dlog_levels
{
	ok,
	fail,
	info,
	warn,
};

void open_stds();
void spawn(char *const []);
void dlog(int, const char *, ...);

#endif
