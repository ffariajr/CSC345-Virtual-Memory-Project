#include "mm.h"

mm* mmInit(char replacementAlgorithm, int totalMemoryFrames) {
  if (v) {
    printf("========== Initializing Memory Manager.\n");
  }
  mm* new = (mm*) malloc(sizeof(mm));
  
  if (replacementAlgorithm == 'f') {
    new->repl = &fifoRepl;
  } else if (replacementAlgorithm == '2') {
    new->repl = &c2Repl;
  } else {
    new->repl = &lruRepl;
  }

  if (v) {
    printf("Replacement Algorithm established.\n");
  }

  new->pids = -1;
  
  if (v) {
    printf("Building Memory.\n");
  }
  
  int x;
  new->freemem = frameInit();
  frame* frptr = new->freemem;

  for (x = 1; x < totalMemoryFrames; x++) {
    frptr->next = frameInit();
    frptr = frptr->next;
  }

  if (v) {
    printf("Memory Initialized.\n");
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

void createProcess(mm* m, pcb* p) {
  m->pids++;
  pt* new = ptInit();
  p->pid = m->pids;
}

int request(mm* m, pcb* p) {
  usleep(10);
  frame* temp = findFrame(m->allocated, p->pid, p->currentPage);

  if (temp) {
    if (v) {
      printf("\tPage Found!\n");
    }
    updateFrame(temp);
    return 1;
  } else if (m->freemem) {
    if (v) {
      printf("\tPage Not Found. Free Frames Available.\n");
    }
    updateFrame(m->freemem);
    pageIn(m, p);
    return 1;
  } else {
    if (v) {
      printf("\tPage Not Found. No Free Frames.\n");
    }
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
  m->allocated->page = p->currentPage;
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
  if (v) {
    printf("<Replacement>");
  }
  usleep(100);
  m->repl(m->allocated);
  frame* temp = m->allocated;
  pageOut(m);
  pageIn(m, p);
  updateFrame(temp);
  if (v) {
    printf("<\\Replacement>\n");
  }
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


