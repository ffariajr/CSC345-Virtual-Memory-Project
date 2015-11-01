#ifndef PCBL_H
#define PCBL_H

#include "imports.h"

//pcb structure
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

//pcbl struct
typedef struct pcbl_t {
  pcb* node;
  struct pcbl_t* next;
  struct pcbl_t* prev;
} pcbl;

//initialize the pcb data structures
pcb* pcbInit(char*, int);

//initialize the pcbl pcb
pcbl* pcblInit();

//roll back last instr
void rollBack(pcb*);

//execute one instr
int pcbStep(pcb*);

//put a new pcbl in the circle
void insert(pcbl**, pcbl*);

//free pcb and pcbl
void pcblDestroy(pcbl*);

//take a pcbl from a circle
void extract(pcbl**);

//free pcb
void pcbDestroy(pcb*);

#endif
