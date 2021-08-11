#include <sys/mount.h>
#include "common.h"

void mount_fss()
{
	if (!(mount("none", "/sys", "sysfs", 0, "")))
	{
		dlog(fail, "Mounting /sys failed!");
	}
	
	if (!(mount("none", "/proc", "procfs", 0, "")))
	{
		dlog(fail, "Mounting /proc failed");
	}
}
