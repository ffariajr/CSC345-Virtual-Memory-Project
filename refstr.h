#ifndef REFSTR_H
#define REFSTR_H

#include "imports.h"
#include <ctype.h>

void genSpatial(char* ref, int pageLimit, int refSize, int v);
void genTemporal(char* ref, int pageStart, int pageLimit, int refSize, int v);
void genSpatialTemporal(char* ref, int pageLimit, int refSize, int v, int st);
void genRandom(char* ref, int pageLimit, int refSize, int v);

#endif
