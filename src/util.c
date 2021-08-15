#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "signals.h"
#include "util.h"

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
			dlog(fail, "execvp failed to execute %s", argv[0]);
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
			return "ok:";

		case fail:
			return "fail:";

		case info:
			return "";

		case warn:
			return "warning:";
	}
}

void dlog(int level, const char *fmt, ...)
{
	char buffer[1000];
	memset(buffer, 0, sizeof(buffer));
	
	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	printf("xenit: %s %s\n", dlog_type(level), buffer);
}
