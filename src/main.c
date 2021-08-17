#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "handler.h"
#include "util.h"

char *const mountcmd[] = { "mount", "-av", NULL };
char *const getty[] = { "/sbin/agetty", "--noclear", "tty1", NULL };

void set_hostname()
{
	char hostname[HOST_NAME_MAX] = {0};
	read_file_content("/etc/hostname", hostname, HOST_NAME_MAX);

	dlog(info, "setting hostname %s", hostname);

	if (sethostname(hostname, HOST_NAME_MAX))
		dlog(fail, "could not set hostname");
	else
		dlog(ok, "set hostname");
}

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

	dlog(info, "opening stds");
	open_stds();

	dlog(info, "xenit is starting");

	mount_tfs();

	dlog(info, "mounting fstab");
	
	spawn(mountcmd);

	set_hostname();

	dlog(info, "starting agetty");
	
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
