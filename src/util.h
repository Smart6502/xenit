#ifndef COMMON_H
#define COMMON_H

enum dlog_levels
{
	ok,
	fail,
	info,
	warn,
};

char *read_file_content(char *file, char *ptr, int len);
void open_stds();
void spawn(char *const []);
void dlog(int, const char *, ...);

void mount_tfs();

#endif
