#include "clock.h"

clock* clockInit(int tquantum) {
  clock* new = (clock*) malloc(sizeof(clock));
  new->time = 0;
  new->tq = tquantum;
  new->list = 0;
  return new;
}

proc* addNewProc(clock* c, int scheduledStart, int refStrIndex) {
  proc* new = (proc*) malloc(sizeof(proc));
  new->startTime = scheduledStart;
  new->refIndex = refStrIndex;
  new->next = 0;
  addProc(c, new);
  return new;
}

void addProc(clock* c, proc* p) {
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

int tick(clock* c) {
  c->time++;
  if (c->tq == -1) {
    return 0;
  } else {
    return !(c->time % c->tq);
  }
}

proc* ltschedule(clock* c) {
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

