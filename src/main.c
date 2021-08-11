#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "common.h"

char *args[] = { "/usr/bin/bash", NULL,};

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

	open_stds();

	dlog(info, "memeic");

	mount_fss();
	execvp(args[0], args);
}
