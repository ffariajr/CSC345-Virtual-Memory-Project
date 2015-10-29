#ifndef CLOK_H
#define CLOK_H

#include "imports.h"
#include "events.h"

typedef struct proc_t {
  int startTime;
  int refIndex;
  struct proc_t* next;
} proc;

typedef struct clok_st {
  int time;
  int tq;
  event* elist;
  proc* list;
} clok;

clok* clokInit(int);
proc* addNewProc(clok*, int, int);
void addProc(clok*, proc*);
void tick(clok*);
proc* ltschedule(clok*);
void clokDestroy(clok*);
void processEvents(clok*);
void addEvent(clok*, event*);

#endif
