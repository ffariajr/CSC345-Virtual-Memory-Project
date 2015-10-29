#ifndef C2_H
#define C2_H

#include "imports.h"
#include "frame.h"

typedef struct c2_t {
  int counter;
  frame** f;
} c2;

void c2Repl(frame**);
int grantChance(void*);

#endif
