#include "clok.h"

clok* clokInit(int tquantum) {
  if (v) {
    printf("Initializing Clock.\n");
  }
  clok* new = (clok*) malloc(sizeof(clok));
  new->time = 0;
  new->tq = tquantum;
  new->list = 0;
  new->elist = 0;
  return new;
}

proc* addNewProc(clok* c, int scheduledStart, int refStrIndex) {
  proc* new = (proc*) malloc(sizeof(proc));
  new->startTime = scheduledStart;
  new->refIndex = refStrIndex;
  new->next = 0;
  addProc(c, new);
  return new;
}

void addProc(clok* c, proc* p) {
  proc* temp = c->list;
  while (temp && temp->next && temp->next->startTime <= p->startTime) {
    temp = temp->next;
  }
  if (!temp) {
    c->list = p;
  } else if (!temp->next) {
    temp->next = p;
  } else {
    p->next = temp->next;
    temp->next = p;
  }
}

void tick(clok* c) {
  if (v) {
    printf("Time: %d\n", c->time);
  }
  c->time++;
  usleep(1);
  if (!(c->time % c->tq)) {
    processEvents(c);
  }
}

proc* ltschedule(clok* c) {
  if (c->list && c->time > c->list->startTime) {
    return (proc*) -1;
  } else if (c->list && c->time == c->list->startTime) {
    proc* tempHead = c->list;
    proc* temp = c->list;
    while (temp && temp->next && temp->next->startTime == c->time) {
      temp = temp->next;
    }
    c->list = temp->next;
    temp->next = 0;
    return tempHead;
  } else {
    return (proc*) 0;
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
    processEvent(temp);
    if (!temp->persistent) {
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
  while (c && c->list && c->list->next) {
    proc* temp = c->list;
    c->list = c->list->next;
    free(temp);
  }
  eventsDestroy(c->elist);
  if (c && c->list) {
    free(c->list);
  }
  free(c);
} 
