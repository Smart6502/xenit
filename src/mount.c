#include <stdio.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include "util.h"

void safe_mount(char *s, char *t, char *f, unsigned long m, void *d)
{
	dlog(info, "mounting %s", t);

	if (mount(s, t, f, m, d))
	{
		perror("mount");
	}
	else
		dlog(ok, "mounted %s", t);
}

void mount_tfs()
{
	unsigned long prsflags = MS_SYNCHRONOUS | MS_NOSUID | MS_NOEXEC;

	mkdir("/proc", S_IFDIR);
	safe_mount("/proc", "/proc", "proc", prsflags, "");

	mkdir("/tmp", S_IFDIR);
	safe_mount("none", "/tmp", "tmpfs", MS_SYNCHRONOUS, "");

	mkdir("/dev/shm", S_IFDIR);
	safe_mount("tmpfs", "/dev/shm", "tmpfs", MS_SYNCHRONOUS, "");
}
