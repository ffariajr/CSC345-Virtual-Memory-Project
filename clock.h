#ifndef CLOCK_H
#define CLOCK_H

#include "imports.h"

typedef struct proc_t {
  int startTime;
  int refIndex;
  struct proc_t* next;
} proc;

typedef struct clock_st {
  int time;
  int tq;
  proc* list;
} clock;

clock* clockInit(int);
proc* addNewProc(clock*, int, int);
void addProc(clock*, proc*);
int tick(clock*);
proc* ltschedule(clock*);

#endif
