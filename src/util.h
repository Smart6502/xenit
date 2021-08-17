#ifndef COMMON_H
#define COMMON_H

enum dlog_levels
{
	ok,
	fail,
	info,
	warn,
};

char *read_file_content(int fd, char *ptr, int len);
void open_stds();
void spawn(char *const []);
void set_hostname();
void dlog(int, const char *, ...);
void mount_tfs();

#endif
