#ifndef FIFO_H
#define FIFO_H

#include "imports.h"
#include "frame.h"

//memory manager calls this to put the page to page out at the top of the list
void fifoRepl(frame**);

#endif
