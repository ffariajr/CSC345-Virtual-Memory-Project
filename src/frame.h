#ifndef FRAME_H
#define FRAME_H

#include "imports.h"

/*
structure of a memory frame
*/
typedef struct frame_t {
  int pid;
  int page;
  int lastUsed;
  struct frame_t* next;
} frame;

//search the frame linked list for a match
frame* findFrame(frame*, int, char);

//initialize the frame 
frame* frameInit();

//unset the frame last used to 0
void updateFrame(frame*);

//set or increment the last used counter
void incrementFrames(frame*);

#endif


