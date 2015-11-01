#ifndef EVENTS_H
#define EVENTS_H

#include "imports.h"

/*
structure of an event
*/
typedef struct event_t {
  int (*behavior)(void*);
  void* data;
  int freeData;
  int freeFunc;
  struct event_t* next;
} event;

//destroy events
void eventsDestroy(event*);

//process this event (execute its function)
int processEvent(event*);

//initialize an event with a function to execute and a data structure to pass to that function when calling it
event* eventInit(int (*)(void*), void*, int, int);

#endif
