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
  data->target = s->readyq;
  data->p = pcblInit();
  data->p->node = pcbInit(ref, size);

  return eventInit(&newToReadyQ, data, 0, 1);
}

int newToReadyQ(void* datum) {
  newQProcData* data = (newQProcData*) datum;
  data->counter++;
  if (data->counter >= data->start) {
    insert(&data->target, data->p);
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

