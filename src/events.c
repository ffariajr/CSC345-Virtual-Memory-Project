#include "events.h"

/*
execute this event's function
return if it should be deleted or not (is persistent)
*/
int processEvent(event* e) {
  if (v) {
    printf("<Processing Event>\n");
    printf("\tDelete Function: %d\n\tDelete Data: %d\n", e->freeFunc, e->freeData);
  }
  int ret = e->behavior(e->data);
  if (v) {
    printf("<\\Processing Event>\n");
  }
  return ret;
}

/*
delete me and my data
*/
void eventsDestroy(event* e) {
  if (v) {
    printf("Destroying Event.\n");
  }
  while (e) {
    event* temp = e;
    e = e->next;
    if (temp->freeData) {
      free(temp->data);
      if (v) {
        printf("\tData Destroyed.\n");
      }
    }
    temp->data = 0;
    if (temp->freeFunc) {
      free(temp->behavior);
      if (v) {
        printf("Function Destroyed.\n");
      }
    }
    temp->behavior = 0;
    free(temp);
  }
}

/*
initialize the event data structures
*/
event* eventInit(int (*event_f)(void*), void* data, int freeFunc, int freeData) {
  event* new = (event*) malloc(sizeof(event));
  new->behavior = event_f;
  new->data = data;
  new->next = 0;
  new->freeFunc = freeFunc;
  new->freeData = freeData;
  return new;
}
