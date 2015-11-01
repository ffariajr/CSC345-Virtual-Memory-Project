#include "frame.h"

/*
memory physical frame
holds a pid and a page
*/
frame* findFrame(frame* list, int pid, char page) {
  frame* temp = list;
  while (temp) {
    if (temp->pid == pid && temp->page == page) {
      return temp;
    }
    temp = temp->next;
  }
  return 0;
}

/*
initialize a memory frame
*/
frame* frameInit() {
  frame* new = (frame*) malloc(sizeof(frame));
  new->pid = -1;
  new->page = -1;
  new->lastUsed = 0;
  new->next = 0;
  return new;
}

/*
set this frame's last used counter to 0
*/
void updateFrame(frame* f) {
  f->lastUsed = 0;
}

/*
in case of lru or 2c, sets or increments the last used counter
*/
void incrementFrames(frame* list) {
  while (list && list->next) {
    list->lastUsed++;
    list = list->next;
  }
  if (list) {
    list->lastUsed++;
  }
}
