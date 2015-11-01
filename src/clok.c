#include "clok.h"
/*
initializes a struct clok_t object
*/
clok* clokInit(int tquantum) {
  if (v) {
    printf("Initializing Clock.\n");
  }
  clok* new = (clok*) malloc(sizeof(clok));
  new->time = 0;
  new->offset = 0;
  new->tq = tquantum;
  new->elist = 0;
  return new;
}

/*
steps forward one unit in time
processes events if at the time quantum
*/
void tick(clok* c) {
  if (v) {
    printf("Ticking.\n");
  }
  c->time++;
  if (!((c->time + c->offset) % c->tq)) {
    processEvents(c);
  }
}

/*
adds an event to the list of events waiting for a time quantum
*/
void addEvent(clok* c, event* e) {
  e->next = c->elist;
  c->elist = e;
}

/*
calls the processEvent function, and deletes the function if it is not persistent
*/
void processEvents(clok* c) {
  if (v) {
    printf("<Processing All Events>\n");
  }
  event* temp = c->elist;
  event* prev = 0;
  while (temp) {
    if (processEvent(temp)) {
      if (prev) {
        prev->next = temp->next;
        temp->next = 0;
        eventsDestroy(temp);
        temp = prev->next;
      } else {
        c->elist = temp->next;
        temp->next = 0;
        eventsDestroy(temp);
        temp = c->elist;
      } 
    } else {
      prev = temp;
      temp = temp->next;
    }
  }
  if (v) {
    printf("<\\Processing All Events>\n");
  }
}

/*
first free the events and their functions and data structures if they so requested
then frees the clock data structure
*/
void clokDestroy(clok* c) {
  eventsDestroy(c->elist);
  free(c);
} 

/*
sets the time quantum to start at this time
*/
void offsetNow(clok* c) {
  c->offset = -c->time;
}

