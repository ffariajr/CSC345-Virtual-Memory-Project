#include "events.h"

void processEvent(event* e) {
  e->behavior(e->data);
}

void eventsDestroy(event* e) {
  while (e) {
    event* temp = e;
    e = e->next;
    if (temp->freeData) {
      free(temp->data);
    }
    temp->data = 0;
    if (temp->freeFunc) {
      free(temp->behavior);
    }
    temp->behavior = 0;
    free(temp);
  }
}

event* eventInit(void (*event_f)(void*), void* data, int persistence, int freeFunc, int freeData) {
  event* new = (event*) malloc(sizeof(event));
  new->behavior = event_f;
  new->persistent = persistence;
  new->data = data;
  new->next = 0;
  new->freeFunc = freeFunc;
  new->freeData = freeData;
  return new;
}
