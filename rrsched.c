#include "rrsched.h"

void rrsched(pcbl** pool, pcbl** dest) {
  if (v) {
    printf("<Round Robin>\n");
  }
  pcbl* temp = *dest;
  if (temp) {
    extract(dest);
    if (v) {
      printf("\tProcess %d Extracted.\n", temp->node->pid);
    }

    if (*pool) {
      *pool = (*pool)->prev;
    }

    insert(pool, temp);
    if (v) {
      printf("\tProcess %d Placed into Ready Queue.\n", temp->node->pid);
    }
    if (*pool) {
      *pool = (*pool)->next;
    }
  }

  temp = *pool;
  if (temp) {
    extract(pool);
    if (v) {
      printf("\tTook Process %d Out of Ready Queue.\n", temp->node->pid);
    }
    insert(dest, temp);
    if (v) {
      printf("\tProcess %d Now in Running Queue.\n", temp->node->pid);
    }
  }
  if (v) {
    printf("<\\Round Robin>\n");
  }
}
