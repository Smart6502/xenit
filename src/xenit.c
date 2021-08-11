#include <signal.h>
#include <stdio.h>
#include <linux/reboot.h>
#include <sys/reboot.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#define AOKSTR "\e[0m[ \e[32;1mOK     \e[0m ]: "
#define INFSTR "\e[0m[ \e[34;1mINFO   \e[0m ]: "
#define WRNSTR "\e[0m[ \e[33;1mWARNING\e[0m ]: "
#define ERRSTR "\e[0m[ \e[31;1mERROR  \e[0m ]: "
#define FTLSTR "\e[0m[ \e[31;1mFATAL  \e[0m ]: "

char* sname = NULL;

void startservice(char* name) {
	printf(INFSTR"Starting service '%s'...\n", name);
	sname = realloc(sname, 12 + strlen(name));
	strcpy(sname, "/etc/xenit/");
	strcat(sname, name);
	char* args[4] = {"bash", "--", sname, NULL};
	pid_t pid = fork();
	if (pid < 0)
	{
		puts(FTLSTR"Internal error: fork() failed.");
	}
	else if (pid == 0)
	{
		pid_t pid2 = fork();
		if (pid2 < 0)
		{
			puts(FTLSTR"Internal error: fork() failed.");
		}
		else if (pid2 == 0)
		{
			execvp("/bin/bash", args);
			puts(FTLSTR"Internal error: execvp() failed.");
			exit(127);
		}
		else if (pid2 > 0)
		{
			int status = 0;
			while (wait(NULL) != pid2) {}
			status = (status >> 8) & 0xFF;
			if (!status)
			{
				printf(AOKSTR"Service '%s' exited successfully.\n", name);
			}
			else
			{
				printf(ERRSTR"Service '%s' exited with code %d.\n", name, status);
			}
			exit(0);
		}
	}
}

void delay(int ms)
{
    struct timespec dts;
    dts.tv_sec = ms / 1000;
    dts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&dts, NULL);
}

int main()
{
	puts(AOKSTR"Started Xenit.");

	sigset_t set;
	int status;

	if (getpid() != 1)
	{
		puts(ERRSTR"Xenit must be run as PID 1.");
		return 1;
	}

	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, 0);

	DIR* cwd = opendir("/etc/xenit");
	if (!cwd) {puts(WRNSTR"No /etc/xenit, no services will be started."); goto noservices;}
	DIR* tmpdir;
	struct dirent* dir;

	while ((dir = readdir(cwd)))
	{
		if (!(tmpdir = opendir(dir->d_name)))
		{
			startservice(dir->d_name);
		}
		else
		{
			closedir(tmpdir);
		}
	}

	puts(INFSTR"Successfully started all services.");

	noservices:

	sigprocmask(SIG_UNBLOCK, &set, 0);

	setsid();
	setpgid(0, 0);

	//puts(INFSTR"Shutting down...");
	//sync();
	//reboot(LINUX_REBOOT_CMD_POWER_OFF);

	puts(INFSTR"Halted.");
	while (1) {delay(1000);}
}

