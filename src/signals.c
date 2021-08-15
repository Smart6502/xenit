#include <linux/reboot.h>
#include <sys/reboot.h>
#include <sys/wait.h>
#include <unistd.h>
#include "signals.h"

sigset_t set;
signal_map sigmap[4] = {
	{ SIGUSR1, sigpoweroff },
	{ SIGCHLD, sigreap     },
	{ SIGALRM, sigreap     },
	{ SIGINT,  sigreboot   },
};

void sigpoweroff(void)
{
	sync();
	reboot(LINUX_REBOOT_CMD_POWER_OFF);
}

void sigreap(void)
{
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
	alarm(TIMEO);
}

void sigreboot(void)
{
	sync();
	reboot(RB_AUTOBOOT);
}
