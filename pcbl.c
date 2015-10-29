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

char pcbStep(pcb* p) {
  if (v) {
    printf("<PCB Step>\n");
  }
  p->runTime++;
  if (p->refPosition < p->refSize) {
    p->currentPage = p->ref[p->refPosition];
    p->refPosition++;
  }
  if (v) {
    printf("<\\PCB Step>\n");
  }
  return p->currentPage;
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
    pcbl* temp = *pos;
    new->next = temp->next;
    new->prev = temp;
    
    new->next->prev = new;
    temp->next = new;
  } else {
    *pos = new;
  }
}

void pcbDestroy(pcb* p) {
  free(p);
  p = 0;
}

void extract(pcbl* p) {
  p->prev->next = p->next;
  p->next->prev = p->prev;

  p->next = p;
  p->prev = p;
}

void pcblDestroy(pcbl* p) {
  if (p && p->next != p) {
    extract(p);
  }
  if (p && p->node) {
    pcbDestroy(p->node);
  }
  free(p);
  p=0;
}


