#ifndef PCBL_H
#define PCBL_H

#include "imports.h"

typedef struct pcb_t {
  int runTime;
  int pid;
  int startTime;
  int endTime;
  int faults;
  char* ref;
  int refPosition;
  int refSize;
  char currentPage;
} pcb;

typedef struct pcbl_t {
  pcb* node;
  struct pcbl_t* next;
  struct pcbl_t* prev;
} pcbl;

pcb* pcbInit(char*, int);
pcbl* pcblInit();

void rollBack(pcb*);
int pcbStep(pcb*);

void insert(pcbl**, pcbl*);
void pcblDestroy(pcbl*);
void extract(pcbl**);
void pcbDestroy(pcb*);

#endif
