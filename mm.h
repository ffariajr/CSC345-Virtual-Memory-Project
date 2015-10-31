#ifndef MM_H
#define MM_H

#include "imports.h"
#include "frame.h"
#include "pcbl.h"
#include "fifo.h"
#include "2c.h"
#include "lru.h"

typedef struct mm_t {
  void (*repl)(frame**);
  int c2counter;
  int pids;
  frame* freemem;
  frame* allocated;
} mm;

mm* mmInit(char, int);

void loadProcess(mm*, pcb*);
int request(mm*, pcb*);
void pageIn(mm*, pcb*);
void pageOut(mm*);
void replacement(mm*, pcb*);
void mmDestroy(mm*);
void mmTerm(mm*, int);

#endif
