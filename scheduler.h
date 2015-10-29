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
  pcbl* waitingq;

  mm* m;
  clok* c;

  void (*sched)(struct sc_t*);
} sc;

typedef struct newQProcData_t {
  int start;
  int counter;
  pcbl* p;
  sc* s;
} newQProcData;

sc* schedInit(char, mm*, clok*);
event* ltSchedule(sc*, char*, int, int);
int newToReadyQ(void*);
void schedDestroy(sc*);

#endif
