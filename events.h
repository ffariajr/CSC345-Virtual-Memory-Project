#ifndef EVENTS_H
#define EVENTS_H

#include "imports.h"

typedef struct event_t {
  void (*behavior)(void*);
  int persistent;
  void* data;
  int freeData;
  int freeFunc;
  struct event_t* next;
} event;

void eventsDestroy(event*);
void processEvent(event*);
event* eventInit(void (*)(void*), void*, int, int, int);

#endif
