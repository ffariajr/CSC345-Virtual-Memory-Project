#include "mm.h"

mm* mmInit(char replacementAlgorithm, int totalMemoryFrames) {
  mm* new = (mm*) malloc(sizeof(mm));
  new->algo = replacementAlgorithm;
  new->pids = -1;
  int x;
  frame* ptr;
  for (x = 0; x < totalMemoryFrames; x++) {
    if (!ptr) {
      ptr = frameInit();
      new->freemem = ptr;
    } else {
      ptr->next = frameInit();
      ptr = ptr->next;
    }
  }
  return new;
}

pt* ptInit() {
  pt* new = (pt*) malloc(sizeof(pt));
  int x;
  for (x = 0; x < 127; x++) {
    new->validPage[x] = 0;
  }
  new->next = 0;
  new->allocated = 0;
  return new;
}

frame* frameInit() {
  frame* new = (frame*) malloc(sizeof(frame));
  new->next = 0;
  return new;
}

void createProcess(mm* m, pcb* p) {
  m->pids++;
  pt* new = ptInit();
  p->ptbl = new;
  p->pid = m->pids;
}

int request(mm* m, pcb* p) {
 return 0;
}

void replacement(mm* m, pcb* p) {
  
}

void mmDestroy(mm* m) {

}

