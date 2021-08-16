#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "handler.h"
#include "util.h"

char *const getty[] = { "/sbin/agetty", "--noclear", "tty1", NULL };

int main(void)
{
	int sig;

	if (getpid() != 1)
	{
		dlog(fail, "Not running as PID 1");

		return 1;
	}

	chdir("/");
	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, NULL);
	
	open_stds();

	dlog(info, "xenit is starting");

	spawn((char *const[]){ "mount", "-av", NULL });

	spawn(getty);

	while (1)
	{
		alarm(TIMEO);
		sigwait(&set, &sig);
		for (size_t i = 0; i < 4; i++)
			if (sigmap[i].sig == sig)
			{
				sigmap[i].handler();
				break;
			}
	}
	
	return 0;
}
