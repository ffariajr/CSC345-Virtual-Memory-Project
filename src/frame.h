#ifndef FRAME_H
#define FRAME_H

#include "imports.h"

typedef struct frame_t {
  int pid;
  int page;
  int lastUsed;
  struct frame_t* next;
} frame;

frame* findFrame(frame*, int, char);
frame* frameInit();
void updateFrame(frame*);
void incrementFrames(frame*);

#endif


