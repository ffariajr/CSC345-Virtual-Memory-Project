#include "mm.h"

mm* mmInit(char replacementAlgorithm, int totalMemoryFrames) {
  mm* new = (mm*) malloc(sizeof(mm));
  new->algo = replacementAlgorithm;
  new->pts = 0;
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

pt* ptInit(int pid) {
  pt* new = (pt*) malloc(sizeof(pt));
  new->pid = pid;
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

int createProcess(mm* m) {
  m->pids++;
  pt* new = ptInit(pids);





  return new->pid;
}

int request(mm* m, int pid, char page) {
  
