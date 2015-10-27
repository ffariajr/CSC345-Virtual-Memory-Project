#ifndef MEM_H
#define MEM_H

typedef struct frame_t {
  struct frame_t* next;
} frame;

typedef struct pt_t {
  char validPage[127];
  struct pt_t* next;
  frame* allocated;
} pt;

#endif


