#ifndef MM_H
#define MM_H

#include "imports.h"

typedef struct frame_t {
  struct frame_t* next;
} frame;

typedef struct pt_t {
  int pid;
  char validPage[127];
  struct pt_t* next;
  frame* allocated;
} pt;

typedef struct mm_t {
  char algo;
  int pids;
  pt* pts;
  frame* freemem;
} mm;

mm* mmInit(char, int);
pt* ptInit(int);
frame* frameInit();

int createProcess(mm*);
int request(mm*, int, char);
void replacement(mm*, int, char);
void destroy(mm*);

#endif
