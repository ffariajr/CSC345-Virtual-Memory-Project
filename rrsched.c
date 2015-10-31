#include "rrsched.h"

void rrsched(pcbl** pool, pcbl** dest) {
  if (v) {
    printf("<Round Robin>\n");
  }
  pcbl* temp = *dest;
  if (temp) {
    extract(dest);
    *pool = (*pool)->prev;
    insert(pool, temp);
    *pool = (*pool)->next;
  }

  temp = *pool;
  extract(pool);
  insert(dest, temp);
  if (v) {
    printf("<\\Round Robin>\n");
  }
}
