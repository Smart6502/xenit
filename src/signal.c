#include <linux/reboot.h>
#include <sys/reboot.h>
#include <unistd.h>

void sig_reboot()
{
	sync();
	reboot(RB_AUTOBOOT);
}

void sig_shutdown()
{
	sync();
	reboot(LINUX_REBOOT_CMD_POWER_OFF);
}
