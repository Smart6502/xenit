#include "common.h"

void dlog_sym(int level)
{
	switch (level)
	{
		case fail:
			printf("\e[1;31m  fail  \e[0m =>");
			break;
		case fatal:
			printf("\e[1;31m  fatal \e[0m =>");
			break;
		case ok:
			printf("\e[1;32m   ok   \e[0m =>");
			break;
		case warn:
			printf("\e[1;33m  warn  \e[0m =>");
			break;
		case info:
			printf("\e[1;34m  info  \e[0m =>");
			break;
	}
}


