#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "handler.h"
#include "util.h"

char *read_file_content(char *file, char *ptr, int len)
{
	int fd = open(file, O_RDONLY);

	struct stat st = {0};
	fstat(fd, &st);

	char *buffer = malloc(st.st_size * sizeof(char));

	if (ptr == NULL)
		read(fd, buffer, st.st_size);
	else
	{
		read(fd, ptr, len);
		buffer = ptr;
	}

	close(fd);

	return buffer;
}

void open_stds()
{
	int ofd = open("/dev/console", O_RDONLY, 0);
	dup2(ofd, STDIN_FILENO);
	int tfd = open("/dev/console", O_RDWR, 0);
	dup2(tfd, STDOUT_FILENO);
	dup2(tfd, STDERR_FILENO);

	if (ofd > 2) close(ofd);
	if (tfd > 2) close(tfd);
}

void spawn(char *const argv[])
{
	switch (fork())
	{
		case 0:
			sigprocmask(SIG_UNBLOCK, &set, NULL);
			setsid();
			execvp(argv[0], argv);
			perror("execvp");
			_exit(1);

		case -1:
			perror("fork");
			dlog(fail, "fork failed");
	}
}

char *dlog_type(int level)
{
	switch (level)
	{
		case ok:
			return "\e[92m ok \e[0m:";

		case fail:
			return "\e[91mfail\e[0m:";

		case info:
			return "\e[94minfo\e[0m:";

		case warn:
			return "\e[93mwarn\e[0m:";
	}
}

void dlog(int level, const char *fmt, ...)
{
	char buffer[1000] = {0};
	
	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	printf("xenit: %s %s\n", dlog_type(level), buffer);
}
