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

	uint64_t runflags = MS_SYNC | MS_NOSUID;

	dlog(info, "Mounting /run...");
	if (!(mount("run", "/run", "tmpfs", runflags, "mode=0755")))
	{
		dlog(fail, "Mounting /run failed");
	}
	else
	{
		dlog(ok, "Mounted /run");
	}
}
