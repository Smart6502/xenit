#include <stdint.h>
#include <stdlib.h>
#include <sys/mount.h>
#include "common.h"

void mount_fstab_fss()
{
	if (access("/etc/fstab", F_OK))
	{
		dlog(fail, "Could not read from /etc/fstab, it does not exist!");
		return;
	}

	FILE *fstab = fopen("/etc/fstab", "r");
	if (fstab == NULL)
	{
		dlog(fail, "Could not open /etc/fstab");
	}

	fseek(fstab, 0, SEEK_END);
	size = ftell(fstab);
	fseek(fstab, 0, SEEK_SET);

	fstab_d = calloc(size + 1, 1);
	fread(fstab_d, 1, size, fstab);	

	free(fstab_d);
	fclose(fstab);
}

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

	mount_fstab_fss();
}
