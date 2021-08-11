#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "common.h"

char *args[] = { "/usr/bin/bash", NULL,};

int main()
{
	sigset_t set;
	int status;

	if (getpid() != 1) return 1;

	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, 0);

	if (fork()) for (;;) wait(&status);

	sigprocmask(SIG_UNBLOCK, &set, 0);

	setsid();
	setpgid(0, 0);

	int onefd = open("/dev/console", O_RDONLY, 0);
	dup2(onefd, 0); // stdin
	int twofd = open("/dev/console", O_RDWR, 0);
	dup2(twofd, 1); // stdout
	dup2(twofd, 2); // stderr

	if (onefd > 2) close(onefd);
	if (twofd > 2) close(twofd);

	dlog(info, "memeic");

	execvp(args[0], args);
}
