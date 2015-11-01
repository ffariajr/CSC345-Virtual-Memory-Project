#ifndef C2_H
#define C2_H

#include "imports.h"
#include "frame.h"

/*
second chance data type
keeps track of a counter to count how many time quantums since the last second chance was granted
and a forgiveness that represents the frequency of granting second chances
*/
typedef struct c2_t {
  int counter;
  int forgiveness;
  frame** f;
} c2;

//called by memory manager during replacement to put the next page to swap out at the top of the list
void c2Repl(frame**);

//called by the event handler when a time quantum is reached
int grantChance(void*);

#endif
