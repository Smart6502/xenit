#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "signals.h"
#include "util.h"

char *const getty[] = { "/sbin/agetty", "tty1", NULL };

int main(void)
{
	int sig;

	if (getpid() != 1)
	{
		dlog("Not running as PID 1");

		return 1;
	}
	
	chdir("/");
	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, NULL);
	
	open_stds();
	dlog("this shit works %d", sig);

	sleep(3);

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
