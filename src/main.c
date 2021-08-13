#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "common.h"

#define LEN(x) (sizeof(x) / sizeof *(x))

sigset_t set;

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
	int sig;
	size_t i;

	dlog(info, "Xenit is starting...");
	
	if (getpid() != 1)
	{
		dlog(fatal, "Xenit must be run as PID 1.");
		return 1;
	}

	chdir("/");

	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, 0);

	open_stds();
	mount_fss();

	while (1)
	{
		alarm(TIMEO);
		sigwait(&set, &sig);

		for (i = 0; i < LEN(sigmap); i++)
			if (sigmap[i].sig == sig)
			{
				sigmap[i].handler();
				break;	
			}
	}

	return 0;
}
