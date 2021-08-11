#include "common.h"

void dlog_sym(int level)
{
	switch (level)
	{
		case fail:
			printf("\e[1;31m  Fail  \e[0m");
			break;
		case fatal:
			printf("\e[1;31m  Fatal \e[0m");
			break;
		case ok:
			printf("\e[1;32m   Ok   \e[0m");
			break;
		case warn:
			printf("\e[1;33m  Warn  \e[0m");
			break;
		case info:
			printf("\e[1;34m  Info  \e[0m");
			break;
	}
}


