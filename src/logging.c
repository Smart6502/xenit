#include "common.h"

void dlog_sym(int level)
{
	switch (level)
	{
		case info:
			fputs("[\e[1;34mi\e[0m]: ", stdout);
			break;
		case ok:
			fputs("[\e[1;32m>\e[0m]: ", stdout);
			break;
		case warn:
			fputs("[\e[1;33m!\e[0m]: ", stdout);
			break;
		case fail:
			fputs("[\e[1;31me\e[0m]: ", stdout);
			break;
		case fatal:
			fputs("[\e[1;31mx\e[0m]: ", stdout);
			break;
		default:
			fputs("[\e[1;37m?\e[0m]: ", stdout);
			break;
	}
}


