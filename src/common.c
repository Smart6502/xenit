#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "signals.h"

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
	}
}
