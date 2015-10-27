#include "pcbl.h"

pcb* pcbInit(char* refs) {
  pcb* new = (pcb*) malloc(sizeof(pcb));
  new->runTime = 0;
  new->startTime = 0;
  new->ref = refs;
  new->refPosition = 0;
  new->next = 0;
  return new;
}

pcbl* pcblInit() {
  pcbl* new = (pcbl*) malloc(sizeof(pcbl));
  new->head = 0;
  new->tail = 0;
  new->size = 0;
  return new;
}

char pcblStep(pcbl* p) {
  return pcbStep(p->head);
}

char pcbStep(pcb* p) {
  p->runTime++;
  p->refPosition++;
  if (p->ref[p->refPosition-1] == '\0') {
    p->refPosition--;
    return ~0;
  } else {
    return p->ref[p->refPosition-1];
  }
}

void rollBack(pcb* p) {
  if (p->ref[p->refPosition] != '\0') {
    p->refPosition--;
  }
}

void pageFault(pcbl* p) {
  rollBack(p->head);
  sendBack(p);
}

void append(pcbl* p, pcb* new) {
  p->size++;
  if (p->size == 1) {
    p->head = new;
    p->tail = new;
  } else {
    p->tail->next = new;
    p->tail = new;
  }
}

void deleteHead(pcbl* p) {
  if (p->size > 0) {
    pcb* temp = p->head;
    p->head = p->head->next;
    p->size--;
    free(temp);
  }
}

void sendBack(pcbl* p) {
  if (p->size > 0) {
    pcb* temp = p->head;
    p->head = p->head->next;
    temp->next = 0;
    append(p, temp);
  }
}

