#include "scheduler.h"

sc* schedInit(char schedulingAlgorithm, mm* m, clok* c) {
  sc* new = (sc*) malloc(sizeof(sc));
  new->runningq = 0;
  new->readyq = 0;

  new->m = m;
  new->c = c;
  new->sched = 0;

  if (schedulingAlgorithm == 'r') {
    new->sched = &rrsched;
    if (v) {
      printf("Round Robin Scheduler Set Up.\n");
    }
  }

  return new;
}

event* ltSchedule(sc* s, char* ref, int size, int start) {
  qProcData* data = (qProcData*) malloc(sizeof(qProcData));
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
  qProcData* data = (qProcData*) datum;
  data->counter++;
  if (data->counter >= data->start) {
    if (v) {
      printf("Opening Program.\n");
    }
    createProcess(data->s, data->p);
    if (v) {
      printf("New Process:\n\tPID:\t\t%d\n\tSize:\t%d\n", data->p->node->pid, data->p->node->refSize);
    }
    return 1;
  }
  return 0;
}

void schedDestroy(sc* s) {
  pcblDestroy(s->runningq);
  pcblDestroy(s->readyq);

  free(s);
  s = 0;
}

int tqPreempt(void* datum) {
  if (v) {
    printf("Preempting Current Active Process.\n");
  }
  sc* s = (sc*) datum;
  s->sched(&s->readyq, &s->runningq);
  return 0;
}

int termActiveProcess(sc* s) {
  if (v) {
    printf("<Terminate Active Process>\n");
  }
  pcbl* p = s->runningq;
  p->node->endTime = s->c->time;
  if (v) {
    printf("Extracting from Running Queue.\n");
  }
  extract(&s->runningq);
  mmTerm(s->m, p->node->pid);

  int ret = 0;
  if (p->node->refPosition != p->node->refSize - 1) {
    ret = -1;
  }
  if (v || output) {
    printf("Process Summary:\nDetail: PID:\t\t%d\nDetail: ", p->node->pid);
    printf("Start Time:\t%d\n", p->node->startTime);
    printf("Detail: End Time:\t%d\nDetail: Time Given:\t%d\n", p->node->endTime, p->node->runTime);
    printf("Detail: Faults:\t\t%d\nDetail: Size:\t\t%d\n", p->node->faults, p->node->refSize);
  }
  pcblDestroy(p);

  if (v) {
    printf("<\\Terminate Active Process>\n");
  }
  return ret;
}

int waitingToRunningQWaiter(void* datum) {
  qProcData* data = (qProcData*) datum;
  data->counter++;
  if (data->counter >= data->start) {
    if (v) {
      printf("Swapping Process Back In.\n");
    }
    
    replacement(data->s->m, data->p->node);
    insert(&data->s->readyq, data->p);

    if (v) {
      printf("Process:\n\tPID:\t\t%d\n\tSize:\t\t%d\n", data->p->node->pid, data->p->node->refSize);
    }
    return 1;
  }
  return 0;
}

