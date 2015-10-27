#include "frame.h"

frame* findFrame(frame* list, int pid, char page) {
  while (list && list->next) {
    if (list->pid == pid && list->page == page) {
      return list;
    }
    list = list->next;
  }
  if (list && list->pid == pid && list->page == page) {
    return list;
  }
  return 0;
}

void updateFrame(frame* f) {
  f->lastUsed = 0;
}

void incrementFrames(frame* list) {
  while (list && list->next) {
    list->lastUsed++;
    list = list->next;
  }
  if (list) {
    list->lastUsed++;
  }
}
