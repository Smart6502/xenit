#include <stdint.h>
#include <sys/mount.h>
#include <stdbool.h>
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

	dmount("proc", "/proc", "procfs", prsflags, "");
	dmount("sys", "/sys", "sysfs", prsflags, "");
	dmount("dev", "/dev", "devtmpfs", MS_NOSUID, "mode=0755");
	dmount("", "/tmp", "none", MS_SYNCHRONOUS, "size=512M");
	dmount("", "/dev/shm", "tmpfs", MS_SYNCHRONOUS, "size=512M");

	dlog(info, "Mounting fstab entries...");
	run("mount", "-av", NULL);

	run("df", NULL);
}
