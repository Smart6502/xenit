#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "common.h"

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

void ttys_init()
{
	char ttyn[4] = "ttyn";

	for (int t = 1; t < 7; t++)
	{
		ttyn[3] = 48 + t;

		run("agetty", ttyn, NULL);
	}
}

int main()
{
	dlog(info, "Xenit is starting...");
	
	chdir("/");

	if (getpid() != 1)
	{
		dlog(fatal, "Xenit must be run as PID 1.");
		return 1;
	}

	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, 0);

	open_stds();
	mount_fss();

	dlogn(info, "Press enter to continue...");
	while (getchar() != '\n') delay(5);

	ttys_init();

	dlog(info, "Xenit halted.");
	
	while (1) delay(1000);
}
