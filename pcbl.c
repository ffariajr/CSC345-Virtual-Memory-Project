#include "pcbl.h"

pcb* pcbInit(char* refs, int size) {
  pcb* new = (pcb*) malloc(sizeof(pcb));
  new->runTime = 0;
  new->startTime = 0;
  new->ref = refs;
  new->currentPage = 0;
  new->refPosition = 0;
  new->refSize = size;
  return new;
}

pcbl* pcblInit() {
  pcbl* new = (pcbl*) malloc(sizeof(pcbl));
  new->node = 0;
  new->next = new;
  new->prev = new;
  return new;
}

int pcbStep(pcb* p) {
  if (v) {
    printf("<PCB Step>\n");
  }
  int ret = 0;
  p->runTime++;
  if (p->refPosition < p->refSize) {
    p->currentPage = p->ref[p->refPosition];
    p->refPosition++;
  } else {
    ret = 1;
  }
  if (v) {
    printf("<\\PCB Step>\n");
  }
  return ret;
}

void rollBack(pcb* p) {
  if (v) {
    printf("<PCB Roll Back>\n");
  }
  if (p->refPosition < p->refSize) {
    p->refPosition--;
  }
  if (v) {
    printf("<\\PCB Roll Back>\n");
  }
}

void insert(pcbl** pos, pcbl* new) {
  if (*pos) {
    new->next = (*pos)->next;
    new->prev = *pos;
    
    (*pos)->next = new;
    new->next->prev = new;

    *pos = new;
  } else {
    *pos = new;
    new->next = new;
    new->prev = new;
  }
}

void pcbDestroy(pcb* p) {
  free(p);
  p = 0;
}

void extract(pcbl** p) {
  if ((*p)->next != *p) {
    *p = (*p)->next;
    pcbl* tempPrev = (*p)->prev;
    
    tempPrev->prev->next = tempPrev->next;
    tempPrev->next->prev = tempPrev->prev;

    tempPrev->next = tempPrev;
    tempPrev->prev = tempPrev;
  } else {
    *p = 0;
  }
}

void pcblDestroy(pcbl* p) {
  if (p && p->next != p) {
    extract(&p);
  }
  if (p && p->node) {
    pcbDestroy(p->node);
  }
  free(p);
  p=0;
}


