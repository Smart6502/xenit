#include "common.h"

void dlog_sym(int level)
{
	switch (level)
	{
		case fail:
			printf("[\e[1;31mx\e[0m]: ");
			break;
		case fatal:
			printf("[\e[1;31mX\e[0m]: ");
			break;
		case ok:
			printf("[\e[1;32m>\e[0m]: ");
			break;
		case warn:
			printf("[\e[1;33m!\e[0m]: ");
			break;
		case info:
			printf("[\e[1;34mi\e[0m]: ");
			break;
	}
}


