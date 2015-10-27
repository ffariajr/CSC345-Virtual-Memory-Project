#ifndef CLOK_H
#define CLOK_H

#include "imports.h"

typedef struct proc_t {
  int startTime;
  int refIndex;
  struct proc_t* next;
} proc;

typedef struct clok_st {
  int time;
  int tq;
  proc* list;
} clok;

clok* clokInit(int);
proc* addNewProc(clok*, int, int);
void addProc(clok*, proc*);
int tick(clok*);
proc* ltschedule(clok*);

#endif
