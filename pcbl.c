#include "pcbl.h"

typedef struct pcb_t {
  int runTime;
  int startTime;
  char* ref;
  int refPosition;
  struct pcb_t* next;
} pcb;

typedef struct pcbl_t {
  pcb* head;
  pcb* tail;
  int size;
} pcbl;

pcb* pcbInit() {
  pcb* new = (pcb*) malloc(sizeof(pcb));
  new->runTime = 0;
  new->startTime = 0;
  new->ref = 0;
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

