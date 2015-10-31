#include "clok.h"

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

void tick(clok* c) {
  if (v) {
    printf("Ticking.\n");
  }
  c->time++;
  usleep(1);
  if (!((c->time + c->offset) % c->tq)) {
    processEvents(c);
  }
}

void addEvent(clok* c, event* e) {
  e->next = c->elist;
  c->elist = e;
}

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

void clokDestroy(clok* c) {
  eventsDestroy(c->elist);
  free(c);
} 

void offsetNow(clok* c) {
  c->offset = -c->time;
}

