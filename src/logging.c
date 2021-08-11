#include "common.h"

void dlog_sym(int level)
{
	switch (level)
	{
		case success:
			printf("\e[1;33m  OK  \e[0m");
			break;
		case fail:
			printf("\e[1;31m FAIL \e[0m");
			break;
		case info:
			printf("\e[1;34m INFO \e[0m");
			break;
	}
}


