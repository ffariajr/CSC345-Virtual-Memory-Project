#include "mm.h"

mm* mmInit(char replacementAlgorithm, int totalMemoryFrames) {
  mm* new = (mm*) malloc(sizeof(mm));
  if (replacementAlgorithm == 'f') {
    new->repl = &fifoRepl;
  } else if (replacementAlgorithm == '2') {
    new->repl = &c2Repl;
  } else {
    new->repl = &lruRepl;
  }
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
  new->allocated = 0;
  return new;
}

pt* ptInit() {
  pt* new = (pt*) malloc(sizeof(pt));
  int x;
  for (x = 0; x < 127; x++) {
    new->validPage[x] = 0;
  }
  new->next = 0;
  return new;
}

frame* frameInit() {
  frame* new = (frame*) malloc(sizeof(frame));
  new->pid = -1;
  new->page = -1;
  new->lastUsed = 0;
  new->next = 0;
  return new;
}

void createProcess(mm* m, pcb* p) {
  m->pids++;
  pt* new = ptInit();
  p->pid = m->pids;
}

int request(mm* m, pcb* p) {
  usleep(10);
  frame* temp = findFrame(m->allocated, p->pid, p->ref[p->refPosition]);
  if (temp) {
    updateFrame(temp);
    return 1;
  } else if (m->freemem) {
    updateFrame(m->freemem);
    pageIn(m, p);
    return 1;
  } else {
    return 0;
  }
}

void pageIn(mm* m, pcb* p) {
  usleep(100);
  frame* temp = m->freemem;
  m->freemem = m->freemem->next;
  temp->next = m->allocated;
  m->allocated = temp;
  m->allocated->pid = p->pid;
  m->allocated->page = p->ref[p->refPosition];
}

void pageOut(mm* m) {
  usleep(200);
  frame* temp = m->allocated;
  m->allocated = m->allocated->next;
  temp->pid = -1;
  temp->page = -1;
  temp->next = m->freemem;
  m->freemem = temp;
}

void replacement(mm* m, pcb* p) {
  usleep(100);
  m->repl(m->allocated);
  frame* temp = m->allocated;
  pageOut(m);
  pageIn(m, p);
  updateFrame(temp);
}

void mmDestroy(mm* m) {
  while (m->freemem && m->freemem->next) {
    frame* temp = m->freemem;
    m->freemem = m->freemem->next;
    free(temp);
  }
  if (m->freemem) {
    free(m->freemem);
  }
  while (m->allocated && m->allocated->next) {
    frame* temp = m->allocated;
    m->allocated = m->allocated->next;
    free(temp);
  }
  if (m->allocated) {
    free(m->allocated);
  }
  free(m);
}






