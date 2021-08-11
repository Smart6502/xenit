#include <stdint.h>
#include <sys/mount.h>
#include "common.h"

void mount_fss()
{
	uint64_t prsflags = MS_SYNCHRONOUS | MS_NOSUID | MS_NOEXEC;

	dlog(info, "Mounting /proc...");
	if (!(mount("proc", "/proc", "procfs", prsflags, "")))
	{
		dlog(fail, "Mounting /proc failed");
	}
	else
	{
		dlog(ok, "Mounted /proc");
	}

	dlog(info, "Mounting /sys...");
	if (!(mount("sys", "/sys", "sysfs", prsflags, "")))
	{
		dlog(fail, "Mounting /sys failed!");
	}
	else
	{
		dlog(ok, "Mounted /sys");
	}

	dlog(info, "Mounting /dev...");
	if (!(mount("dev", "/dev", "devtmpfs", MS_NOSUID, "mode=0755")))
	{
		dlog(fail, "Mounting /dev failed");
	}
	else
	{
		dlog(ok, "Mounted /dev");
	}
}
