#ifndef CLOK_H
#define CLOK_H

#include "imports.h"
#include "events.h"

typedef struct clok_st {
  int time;
  int tq;
  event* elist;
  int offset;
} clok;

clok* clokInit(int);
void tick(clok*);
void clokDestroy(clok*);
void processEvents(clok*);
void addEvent(clok*, event*);

#endif
