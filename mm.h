#ifndef MM_H
#define MM_H

#include "imports.h"
#include "frame.h"
#include "pcbl.h"
#include "fifo.h"
#include "2c.h"
#include "lru.h"

typedef struct pt_t {
  char validPage[127];
  struct pt_t* next;
} pt;

typedef struct mm_t {
  void (*repl)(frame**);
  int pids;
  frame* freemem;
  frame* allocated;
} mm;

mm* mmInit(char, int);
pt* ptInit();

void createProcess(mm*, pcb*);
int request(mm*, pcb*);
void pageIn(mm*, pcb*);
void pageOut(mm*);
void replacement(mm*, pcb*);
void mmDestroy(mm*);

#endif
