#ifndef PCBL_H
#define PCBL_H

#include "imports.h"

struct pcb_t* pcbInit();
struct pcbl_t* pcblInit();

void append(struct pcbl_t*, struct pcb_t*);
void deleteHead(struct pcbl_t*);
void sendBack(struct pcbl_t*);

#endif
