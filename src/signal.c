#include <linux/reboot.h>
#include <signal.h>
#include <sys/reboot.h>
#include <wait.h>
#include <unistd.h>
#include "common.h"

void sigreap()
{
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
	alarm(TIMEO);
}

void sigreboot()
{
	sync();
	reboot(RB_AUTOBOOT);
}

void sigpoff()
{
	sync();
	reboot(LINUX_REBOOT_CMD_POWER_OFF);
}

sighandler sigmap[] = {
	{ SIGUSR1, sigpoff },
	{ SIGCHLD, sigreap },
	{ SIGALRM, sigreap },
	{ SIGINT, sigreboot },
};
