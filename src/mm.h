#ifndef MM_H
#define MM_H

#include "imports.h"
#include "frame.h"
#include "pcbl.h"
#include "fifo.h"
#include "2c.h"
#include "lru.h"

//structure of the memory manager
typedef struct mm_t {
  void (*repl)(frame**);
  int c2counter;
  int pids;
  frame* freemem;
  frame* allocated;
} mm;

//initialize mem manager data structs
mm* mmInit(char, int);

//give a process a new pid
void loadProcess(mm*, pcb*);

//answer if the page is in mem
int request(mm*, pcb*);

//bring a page from freemem list to allocated
void pageIn(mm*, pcb*);

//take a page from allocated and put in freemem list
void pageOut(mm*);

//swap the head of allocated with the head of freemem
void replacement(mm*, pcb*);

//free all frames and then myself
void mmDestroy(mm*);

//free that processes pages
void mmTerm(mm*, int);

#endif
