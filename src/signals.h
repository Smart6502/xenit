#ifndef SIGNALS_H
#define SIGNALS_H
#include <signal.h>

#define TIMEO 30

extern sigset_t set;

void sigpoweroff(void);
void sigreap(void);
void sigreboot(void);

typedef struct
{
	int sig;
	void (*handler)(void);
} signal_map;

extern signal_map sigmap[4];

#endif
