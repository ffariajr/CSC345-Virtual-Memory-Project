#ifndef MEM_H
#define MEM_H

typedef struct frame_t {
  int pid;
  int page;
  struct frame_t* next;
} frame;

typedef struct pt_t {
  char validPage[127];
  struct pt_t* next;
} pt;

#endif


