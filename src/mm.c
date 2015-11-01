#include "mm.h"

//initialize the memory manager
//decides the replacement algo
//builds free frames
mm* mmInit(char replacementAlgorithm, int totalMemoryFrames) {
  if (v) {
    printf("<Memory Manager Initialization>\n");
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
  new->c2counter = 0;
  
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
    printf("<\\Memory Manager Initialization>\n");
  }

  new->allocated = 0;
  return new;
}

//assigns a pid to a new process
void loadProcess(mm* m, pcb* p) {
  m->pids++;
  p->pid = m->pids;
}

//returns if that page is in memory
int request(mm* m, pcb* p) {
  frame* temp = findFrame(m->allocated, p->pid, p->currentPage);

  if (temp) {
    if (v) {
      printf("\t\t\tPage Found!\n");
    } else if (memoutput) {
      printf("\tHIT\n");
    }
    updateFrame(temp);
    return 1;
  } else if (m->freemem) {
    if (v) {
      printf("\t\t\tPage Not Found. Free Frames Available.\n");
    } else if (memoutput) {
      printf("\t + Free Memory Frames Available\n");
    }
    pageIn(m, p);
    updateFrame(m->allocated);
    return 1;
  } else {
    p->faults++;
    if (v) {
      printf("\t\t\tPage Not Found. No Free Frames.\n");
    } else if (memoutput) {
      printf("\t - Replacement Required\n");
    }
    return 0;
  }
}

//bring a page in from "disk" into a frame that should be at the head of the freemem list before calling this
void pageIn(mm* m, pcb* p) {
  if (v) {
    printf("<Page In>\n");
  }
  frame* temp = m->freemem;
  m->freemem = m->freemem->next;
  temp->next = m->allocated;
  m->allocated = temp;
  m->allocated->pid = p->pid;
  m->allocated->page = p->currentPage;
  if (v) {
    printf("<\\Page In>\n");
  }
}

//take a page out of memory to make room
void pageOut(mm* m) {
  if (v) {
    printf("<Page Out>\n");
  }
  if (m->allocated) {
    frame* temp = m->allocated;
    m->allocated = m->allocated->next;
    temp->pid = -1;
    temp->page = -1;
    temp->lastUsed = 0;
    temp->next = m->freemem;
    m->freemem = temp;
  }
  if (v) {
    printf("<\\Page Out>\n");
  }
}

//replace the frame at the head of the allocated list with the new page
void replacement(mm* m, pcb* p) {
  if (v) {
    printf("<Replacement>\n");
  }
  m->repl(&m->allocated);

  if (v) {
    printf("Replacement Algorithm Finished.\n");
  }

  int victimPID = m->allocated->pid;
  int victimPage = m->allocated->page;
  int victimLRU = m->allocated->lastUsed;
  pageOut(m);
  if (v) {
    printf("Evicted Frame: [ < %4d , %3d > , %5d ]\n", victimPID, victimPage, victimLRU);
  }
  pageIn(m, p);
  updateFrame(m->allocated);
  if (v) {
    printf("<\\Replacement>\n");
  }
}

//free all frames and then myself
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

//free the dying processes frames
void mmTerm(mm* m, int pid) {
  if (v) {
    printf("<MM Process Termination>\n");
  }
  frame* temp = m->allocated;
  frame* prev = 0;
  while (temp) {
    if (temp->pid == pid) {
      if (prev) {
        prev->next = temp->next;
      } else {
        m->allocated = temp->next;
      }
      temp->next = m->freemem;
      m->freemem = temp;
      temp->pid = -1;
      temp->page = -1;
      temp->lastUsed = 0;
      if (prev) {
        temp = prev->next;
      } else {
        temp = m->allocated;
      }
    } else {
      prev = temp;
      temp = temp->next;
    }
  }
  if (v) {
    printf("<\\MM Process Termination>\n");
  }
}


