#include <linux/reboot.h>
#include <sys/reboot.h>
#include <signal.h>
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

void setup_signals()
{
	signal(SIGINT, sig_reboot);
}
