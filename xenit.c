#include <linux/reboot.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEN(x)	(sizeof (x) / sizeof *(x))
#define TIMEO	30

static void sigpoweroff(void);
static void sigreap(void);
static void sigreboot(void);
static void spawn(char *const []);

static struct
{
	int sig;
	void (*handler)(void);

} sigmap[] = {
	{ SIGUSR1, sigpoweroff },
	{ SIGCHLD, sigreap     },
	{ SIGALRM, sigreap     },
	{ SIGINT,  sigreboot   },
};

static sigset_t set;

int main(void)
{
	int sig;

	if (getpid() != 1)
		return 1;
	
	chdir("/");
	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, NULL);
	
	while (1)
	{
		alarm(TIMEO);
		sigwait(&set, &sig);
		for (size_t i = 0; i < LEN(sigmap); i++)
			if (sigmap[i].sig == sig)
			{
				sigmap[i].handler();
				break;
			}
	}
	
	return 0;
}

static void sigpoweroff(void)
{
	sync();
	reboot(LINUX_REBOOT_CMD_POWER_OFF);
}

static void sigreap(void)
{
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
	alarm(TIMEO);
}

static void sigreboot(void)
{
	sync();
	reboot(RB_AUTOBOOT);
}

static void spawn(char *const argv[])
{
	switch (fork())
	{
		case 0:
			sigprocmask(SIG_UNBLOCK, &set, NULL);
			setsid();
			execvp(argv[0], argv);
			perror("execvp");
			_exit(1);
		case -1:
			perror("fork");
	}
}
