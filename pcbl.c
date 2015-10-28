#include "pcbl.h"

pcb* pcbInit(char* refs, int size) {
  pcb* new = (pcb*) malloc(sizeof(pcb));
  new->runTime = 0;
  new->startTime = 0;
  new->ref = refs;
  new->currentPage = 0;
  new->refPosition = 0;
  new->refSize = size;
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
  if (v) {
    printf("<PCB Step>\n");
  }
  p->runTime++;
  if (p->currentPage != ~0) {
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
  if (p->currentPage != ~0) {
    p->refPosition--;
  }
  if (v) {
    printf("<\\PCB Roll Back>\n");
  }
}

void pageFault(pcbl* p) {
  if (v) {
    printf("<Page Fault>\n");
  }
  rollBack(p->head);
  sendBack(p);
  if (v) {
    printf("<\\Page Fault>\n");
  }
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

void pcbDestroy(pcb* p) {
  free(p);
}

void pcblDestroy(pcbl* p) {
  while (p && p->head) {
    pcb* temp = p->head;
    p->head = p->head->next;
    pcbDestroy(temp);
  }
  if (p->head) {
    pcbDestroy(p->head);
  }
  free(p);
}


