#include <signal.h>
#include <stdio.h>
#include <sys/reboot.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#define AOKSTR "\e[0m[ \e[32mOK     \e[0m ]: "
#define INFSTR "\e[0m[ \e[34mINFO   \e[0m ]: "
#define WRNSTR "\e[0m[ \e[33mWARNING\e[0m ]: "
#define ERRSTR "\e[0m[ \e[31mERROR  \e[0m ]: "
#define FTLSTR "\e[0m[ \e[36mFATAL  \e[0m ]: "

int main()
{
	sigset_t set;
	int status;

	if (getpid() != 1) return 1;

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
			if (dir->d_name[0] == '-')
			{
				printf(ERRSTR"Invalid service name: '%s'.\n", dir->d_name);
				continue;
			}
			printf(INFSTR"Starting service '%s'...", dir->d_name);
			pid_t pid = fork();
			if (pid < 0)
			{
				puts(FTLSTR"Internal error: fork() failed.");
			}
			else if (pid == 0)
			{
				char* args[3] = {"bash", dir->d_name, NULL};
				execvp("/bin/bash", args);
				puts(FTLSTR"Internal error: execvp() failed.");
				exit(0);
			}
			else if (pid > 0)
			{
				int status;
				while (wait(NULL) != pid) {}
				status = (status >> 8) & 0xFF;
				if (!status)
				{
					printf(AOKSTR"Service '%s' exited successfully.", dir->d_name);
				}
				else
				{
					printf(ERRSTR"Service '%s' exited with code %d.", dir->d_name, status);
				}
			}
		}
		else
		{
			closedir(tmpdir);
		}
	}

	noservices:

	sigprocmask(SIG_UNBLOCK, &set, 0);

	setsid();
	setpgid(0, 0);

	printf("xenit is starting...\n");
	printf("Rebooting...\n");

	execvp("/usr/bin/bash", NULL);
}
