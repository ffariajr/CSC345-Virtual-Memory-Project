#ifndef CLOK_H
#define CLOK_H

#include "imports.h"
#include "events.h"

/*
system clock
*/
typedef struct clok_st {
  int time;
  int tq;
  event* elist;
  int offset;
} clok;

//initializes the clock data structure
clok* clokInit(int);

//steps forward one time unit
void tick(clok*);

//free the clocks events and then the clock itself
void clokDestroy(clok*);

//calles each event's processEvent, then deletes it if it is not persistent
void processEvents(clok*);

//adds the event to the list of events
void addEvent(clok*, event*);

//sets the time quantum to start at this time
void offsetNow(clok*);

#endif
