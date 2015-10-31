#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "imports.h"
#include "clok.h"
#include "pcbl.h"
#include "mm.h"
#include "events.h"
#include "rrsched.h"

typedef struct sc_t {
  pcbl* runningq;
  pcbl* readyq;

  mm* m;
  clok* c;

  void (*sched)(pcbl**, pcbl**);
} sc;

typedef struct qProcData_t {
  int start;
  int counter;
  pcbl* p;
  sc* s;
} qProcData;

sc* schedInit(char, mm*, clok*);
event* ltSchedule(sc*, char*, int, int);
int newToReadyQWaiter(void*);
void schedDestroy(sc*);
void createProcess(sc*, pcbl*);
int tqPreempt(void*);
int termActiveProcess(sc* s);
int waitingToRunningQWaiter(void*);

#endif
