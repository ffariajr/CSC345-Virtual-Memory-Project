#ifndef RRSCHED_H
#define RRSCHED_H

#include "imports.h"
#include "pcbl.h"
#include "scheduler.h"

typedef struct sc_t sc;

void rrsched(sc*);
void preempt(sc*);
void pickNew(sc*);

#endif
