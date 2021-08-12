#include <stdint.h>
#include <sys/mount.h>
#include <stdbool.h>
#include "common.h"

void shiftstrdown(char* line, int32_t chars) {
	int32_t iptr;
	for (iptr = 0; line[chars]; ++chars, ++iptr) {
		line[iptr] = line[chars];
	}
	line[iptr] = 0;
}

void mount_fss()
{
	uint64_t prsflags = MS_SYNCHRONOUS | MS_NOSUID | MS_NOEXEC;

	dlog(info, "Mounting /proc...");
	if (mount("proc", "/proc", "procfs", prsflags, ""))
	{
		dlog(ok, "Mounted /proc.");
	}
	else
	{
		dlog(fail, "Mounting /proc failed.");
	}

	dlog(info, "Mounting /sys...");
	if (mount("sys", "/sys", "sysfs", prsflags, ""))
	{
		dlog(ok, "Mounted /sys.");
	}
	else
	{
		dlog(fail, "Mounting /sys failed.");
	}

	dlog(info, "Mounting /dev...");
	if (mount("dev", "/dev", "devtmpfs", MS_NOSUID, "mode=0755"))
	{
		dlog(ok, "Mounted /dev.");
	}
	else
	{
		dlog(fail, "Mounting /dev failed.");
	}

	dlog(info, "Mounting fstab entries...");
	run("mount", "-a", NULL);

	run("df", NULL);
}
