#ifndef PCBL_H
#define PCBL_H

#include "imports.h"

typedef struct pcb_t {
  int runTime;
  int pid;
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

pcb* pcbInit(char*);
pcbl* pcblInit();

void rollBack(pcb*);
char pcblStep(pcbl*);
char pcbStep(pcb*);
void pageFault(pcbl*);

void append(pcbl*, pcb*);
void deleteHead(pcbl*);
void sendBack(pcbl*);

void pcblDestroy(pcbl*);
void pcbDestroy(pcb*);

#endif
