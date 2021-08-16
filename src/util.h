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
int spawn(char *const []);
void safe_spawn(char *const[]);
void dlog(int, const char *, ...);

#endif
