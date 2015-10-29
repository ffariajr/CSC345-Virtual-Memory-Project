#include "scheduler.h"

sc* schedInit(char schedulingAlgorithm, mm* m, clok* c) {
  sc* new = (sc*) malloc(sizeof(sc));
  new->runningq = 0;
  new->readyq = 0;
  new->waitingq = 0;

  new->m = m;
  new->c = c;
  new->sched = 0;

  if (schedulingAlgorithm == 'r') {
    new->sched = &rrsched;
  }

  return new;
}

event* ltSchedule(sc* s, char* ref, int size, int start) {
  newQProcData* data = (newQProcData*) malloc(sizeof(newQProcData));
  data->start = start;
  data->counter = 0;
  data->s = s;
  data->p = pcblInit();
  data->p->node = pcbInit(ref, size);

  return eventInit(&newToReadyQWaiter, data, 0, 1);
}

void createProcess(sc* s, pcbl* p) {
  loadProcess(s->m, p->node);
  insert(&s->readyq, p);
  p->node->startTime = s->c->time;
}
  
int newToReadyQWaiter(void* datum) {
  newQProcData* data = (newQProcData*) datum;
  data->counter++;
  if (data->counter >= data->start) {
    createProcess(data->s, data->p);
    data->p=0;
    return 1;
  }
  return 0;
}

void schedDestroy(sc* s) {
  pcblDestroy(s->runningq);
  pcblDestroy(s->readyq);
  pcblDestroy(s->waitingq);

  free(s);
  s = 0;
}

int tqPreempt(void* datum) {
  sc* s = (sc*) datum;


