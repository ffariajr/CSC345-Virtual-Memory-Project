#ifndef MM_H
#define MM_H

#include "imports.h"
#include "memory.h"
#include "pcbl.h"

typedef struct mm_t {
  char algo;
  int pids;
  frame* freemem;
  frame* allocated;
} mm;

mm* mmInit(char, int);
pt* ptInit();
frame* frameInit();

void createProcess(mm*, pcb*);
int request(mm*, pcb*);
void pageIn(mm*, pcb*);
void pageOut(mm*);
void replacement(mm*, pcb*);
void mmDestroy(mm*);

#endif
