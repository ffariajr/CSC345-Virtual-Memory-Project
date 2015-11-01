#ifndef LRU_H
#define LRU_H

#include "imports.h"
#include "frame.h"

//caled by memory manager to find next page to page out
void lruRepl(frame**);

#endif
