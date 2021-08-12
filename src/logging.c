#include "common.h"

void dlog_sym(int level)
{
	switch (level)
	{
		case info:
			fputs("\e[1;34m[i]\e[0m: ", stdout);
			break;
		case ok:
			fputs("\e[1;32m[>]\e[0m: ", stdout);
			break;
		case warn:
			fputs("\e[1;33m[!]\e[0m: ", stdout);
			break;
		case fail:
			fputs("\e[1;31m[e]\e[0m: ", stdout);
			break;
		case fatal:
			fputs("\e[1;31m[x]\e[0m: ", stdout);
			break;
		default:
			fputs("\e[1;37m[?]\e[0m: ", stdout);
			break;
	}
}


