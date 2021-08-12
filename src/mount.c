#include <stdint.h>
#include <sys/mount.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "common.h"

int dmount(char *s, char *t, char *f, unsigned long m, void *d) {
	dlog(info, "Mounting %s...", t);
	int ret;
	if ((ret = mount(s, t, f, m, d)))
	{
		dlog(fail, "Mounting %s failed, errno %d (%s).", t, errno, strerror(errno));
	}
	else
	{
		dlog(ok, "Mounted %s.", t);
	}
	return ret;
}

void mount_fss()
{
	uint64_t prsflags = MS_SYNCHRONOUS | MS_NOSUID | MS_NOEXEC;

	mkdir("/proc", S_IFDIR);
	dmount("/proc", "/proc", "proc", prsflags, "");
	mkdir("/tmp", S_IFDIR);
	dmount("/tmp", "/tmp", "tmpfs", MS_SYNCHRONOUS, "");
	mkdir("/dev/shm", S_IFDIR);
	dmount("", "/dev/shm", "tmpfs", MS_SYNCHRONOUS, "");

	dlog(info, "Mounting fstab entries...");
	run("mount", "-av", NULL);

	run("df", NULL);
}
