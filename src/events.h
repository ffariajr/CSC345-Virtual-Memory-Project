#ifndef EVENTS_H
#define EVENTS_H

#include "imports.h"

typedef struct event_t {
  int (*behavior)(void*);
  void* data;
  int freeData;
  int freeFunc;
  struct event_t* next;
} event;

void eventsDestroy(event*);
int processEvent(event*);
event* eventInit(int (*)(void*), void*, int, int);

#endif
