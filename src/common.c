#include <stdio.h>
#include <unistd.h>
#include "signals.h"

void spawn(char *const argv[])
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
