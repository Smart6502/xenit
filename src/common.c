#include <sys/wait.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>
#include "common.h"

int run(char* name, ...)
{
	int status = -1;
	char** args = malloc(2 * sizeof(char*));
	va_list vargs;
	va_start(vargs, name);
	args[0] = name;
	for (int i = 1; (args[i] = va_arg(vargs, char*));) {
	    args = realloc(args, (++i + 1) * sizeof(char*));
    }
	va_end(vargs);
	pid_t pid = fork();
	if (pid < 0)
	{
		fatalfunc("fork", pid);
	}
	else if (pid == 0)
	{
		sigprocmask(SIG_UNBLOCK, &set, 0);
		dlog(info, "Executing %s...", args[0]);
		int r = execvp(args[0], args);
		fatalfunc("execvp", r);
		exit(127);
	}
	else if (pid > 0)
	{
		while (wait(&status) != pid) {}
		status = (status >> 8) & 0xFF;
		if (status == 127)
		{
			dlog(fatal, "Possible execvp() failure due to child return code of 127.");
		}
		else if (status)
		{
			dlog(fail, "%s exited with code %d.", args[0], status);
		}
		else
		{
			dlog(ok, "%s exited successfully.", args[0]);
		}
	}
	free(args);
	return status;
}

void delay(int ms)
{
    struct timespec dts;
    dts.tv_sec = ms / 1000;
    dts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&dts, NULL);
}
