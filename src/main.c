#include <signal.h>
#include <stdio.h>
#include <sys/reboot.h>
#include <sys/wait.h>
#include <unistd.h>
#include "common.h"

char *args[] = { NULL,};

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

	dlog(info, "memeic");

	execvp("/usr/bin/bash", args);
}
