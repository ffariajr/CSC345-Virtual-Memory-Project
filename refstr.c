#include "refstr.h"

extern const char* __progname;

typedef struct slocality_t {
  char initialPage;
  int range;
  int affinity;
  struct slocality_t* next;
} slocality;

typedef struct tlocality_t {
  char page;
  struct tlocality_t* next;
} tlocality;

int main(int argc, char** argv) {
  
  int v = 0;
  char reftype = 'r';
  char* outputFileName = 0;
  char outputType = 0;
  int pageLimit = 100;
  int refSize = 250;

  int z;
  for (z = 1; z < argc; z++) {
    const char* arg = argv[z];
  
    if (!strcmp(arg, "-h")) {
      printf("Usage of this program is as follows:\n");
      printf("\t%s [-v] [spatial | temporal | both | random] [-o <outputFile> <a | w>] [-refS", argv[0]);
      printf("ize <#>] [-pageLimit <#>]");
      printf("\n\t\t-v\n\t\t\tVerbose output\n\t\tspatial | temporal | both | random\n\t\t\tspatial: referenc");
      printf("e string displays spatial");
      printf(" locality.\n\t\t\ttemporal: reference string displays temporal locality\n\t\t\tboth: reference");
      printf(" string ");
      printf("displays both temporal and spatial locality\n\t\t\trandom: reference string is random.  this is the");
      printf(" default behavior.\n\t\t-o <outp");
      printf("utfile> <a | w>\n\t\t\tgenerates reference string into a file.  a to append, w to overwrite\n\t");
      printf("\t\tdefault behavior is to output to STDOUT\n\t");
      printf("\t-refSize <#>\n\t\t\treference string will be of size <#>\n\t\t\tdefault is size 250\n\t\t-page");
      printf("Limit <#>\n\t\t\treference s");
      printf("tring will display pages from 1-<#>\n\t\t\t<#> must be greater than 1 and less than 128\n\t\t\td");
      printf("efault is 1-100\n");
      exit(0);
    } else if (!strcmp(arg, "spatial")) {
      reftype = 's';
    } else if (!strcmp(arg, "temporal")) {
      reftype = 't';
    } else if (!strcmp(arg, "both")) {
      reftype = 'b';
    } else if (!strcmp(arg, "random")) {
      reftype = 'r';
    } else if (!strcmp(arg, "-o")) {
      z++;
      if (z < argc) {
	outputFileName = argv[z];
      } else {
	printf("Fatal Error: Destination file must succeed '-o' argument.\nQuitting NOW...\n");
	exit(-1);
      }
      z++;
      if (z < argc) {
	if (!strcmp(argv[z], "a")) {
	  outputType = 'a';
	} else if (!strcmp(argv[z], "w")) {
	  outputType = 'w';
	} else {
	  printf("Fatal Error: Bad file output operation: %s\nWill Quit...\n", argv[z]);
	  exit(-1);
	}
      }
    } else if (!strcmp(arg, "-v")) {
      v = 1;
    } else if (!strcmp(arg, "-pageLimit")) {
      z++;
      if (z < argc) {
	int zz = 0;
	char valid = 1;
	while (argv[z][zz] != '\0') {
	  if (!isdigit(argv[z][zz])) {
	    valid = 0;
	  }
	  zz++;
	}
	pageLimit = atoi(argv[z]);
	if (pageLimit < 2 || pageLimit > 127) {
	  printf("Fatal Error: Invalid page numbering: %d\nQuitting NOW...\n", pageLimit);
	  exit(-1);
	}
      } else {
	printf("Fatal Error: Max virtual page limit must succeed '-pageLimit' argument.\nQuitting NOW...\n");
	exit(-1);
      }
    } else if (!strcmp(arg, "-refSize")) {
      z++;
      if(z < argc) {
	int zz = 0;
	char valid = 1;
	while (argv[z][zz] != '\0') {
	  if (!isdigit(argv[z][zz])) {
	    valid = 0;
	  }
	  zz++;
	}
	if (valid) {
	  refSize = atoi(argv[z]);
	  if (refSize < 1) {
	    printf("Fatal Error: Invalid reference string size: %d\nQuitting NOW...\n", refSize);
	    exit(-1);
	  }
	} else {
	  printf("Fatal Error: Invalid argument %s\nQuitting NOW...\n", argv[z]);
	  exit(-1);
	}
      }
    } else {
      printf("Fatal Error: Invalid argument: %s\nQuitting...\n", arg);
      exit(-1);
    }
  }

  char* ref = (char*) malloc(sizeof(char) * refSize+1);
  if (!ref) {
    printf("Fatal Error: Not enough memory for reference string of size: %d\nQuitting NOW...\n", refSize);
    exit(-2);
  }
  ref[refSize] = '\0';

  if (v) {
    printf("Starting Calculation of Reference String\n");
  }

  if (reftype == 's') {
    genSpatial(ref, pageLimit, refSize, v);
  } else if (reftype == 't') {
    genTemporal(ref, 1, pageLimit, refSize, v);
  } else if (reftype == 'b') {
    genSpatialTemporal(ref, pageLimit, refSize, v, 1);
  } else {
    genRandom(ref, pageLimit, refSize, v);
  }
  
  if (v) {
    printf("Finished Calculation of Reference String\n");
    printf("Reference String is: \t %s\n", ref);
  }

  if (outputType) {

    if (v) {
      printf("Opening file %s...\n", outputFileName);
    }

    FILE* f = fopen(outputFileName, &outputType);

    if (!f) {
      printf("Failed to open file %s\nQuitting...\n", outputFileName);
      exit(-2);
    }

    if (v) {
      printf("File opened successfully!\n");
    }
    
    if (outputType == 'a') {
      char delim = ~0;
      fputc(delim, f);
    }

    fputs(ref, f);

    if (v) {
      printf("Successfully wrote to file\n");
    }

    fclose(f);

    if (v) {
      printf("Successfully closed file!\n");
    }
  } else {
    if (v) {
      printf("Printing pages:\n");
    }

    int x;
    for (x = 0; x < refSize; x++) {
      printf("%d ", ref[x]);
    }
    printf("\n");
  }

  if (v) {
    printf("End\n");
  }
}

void genSpatial(char* ref, int pageLimit, int refSize, int v) {
  genSpatialTemporal(ref, pageLimit, refSize, v, 0);
}

void genTemporal(char* ref, int pageStart, int pageLimit, int refSize, int v) {
  
  if (v) {
    printf("genTemporal()\n");
    printf("Randomizing randoms\n");
  }
  
  const char rft = 'r';
  FILE* rf = fopen("/dev/urandom", &rft);
  char r = fgetc(rf);
  fclose(rf);
  srand(r);

  if (v) {
    printf("Generating String\n");
  }
  
  tlocality* head = 0;
  tlocality* tail = 0;
  
  int pages = pageLimit-pageStart;
  int x;
  for (x = 0; x <= pages; x++) {
    tlocality* temp = (tlocality*) malloc(sizeof(tlocality));
    if (!temp) {
      printf("Fatal Error: Could not create a new locality.\nQuitting NOW...\n");
      if (v) {
        printf("PageStart: %d\nPageLimit: %d\nRefSize: %d\n", pageStart, pageLimit, refSize);
      }
      exit(-2);
    }
    if (!x) {
      tail = temp;
    }
    temp->page = pageStart + x;
    temp->next = head;
    head = temp;
  }
  
  int references = 0;
  while (references < refSize) {
    int look = rand() % (pages * 2);
    tlocality* prev = 0;
    tlocality* focus = head;
    while (focus->next && look > 0) {
      prev = focus;
      focus = focus->next;
      look--;
    }
    
    ref[references] = focus->page;
    if (tail != focus) {
      if (head == focus) {
        head = focus->next;
      } else {
        prev->next = focus->next;
      }
    
      focus->next = 0;
      tail->next = focus;
      tail = focus;
    }
    
    references++;
  }
  
  if (v) {
    printf("Freeing allocated memory\n");
  }
  
  while (head) {
    tlocality* temp = head;
    head = head->next;
    free(temp);
  }
  
  
  if (v) {
    printf("Done with genTemporal()\n");
  }
}

void genSpatialTemporal(char* ref, int pageLimit, int refSize, int v, int st) {
  if (v) {
    if (!st) {
      printf("genSpatial()\n");
    } else {
      printf("genSpatialTemporal()\n");
    }
    printf("Randomizing randoms\n");
  }

  const char rft = 'r';
  FILE* rf = fopen("/dev/urandom", &rft);
  char r = fgetc(rf);
  fclose(rf);
  srand(r);

  if (v) {
    printf("Generating String\n");
  }

  int references = 0;
  slocality* head = 0;

  while (references < refSize) {
    
    if (head && head->next && ((rand() % 10) > 4)) {
      slocality* temp = head;
      head = head->next;
      free(temp);
      if (head->affinity > refSize-references) {
        head->affinity = refSize-references;
      }
    } else {
      int aff = rand() % 40 + 10;
      if (aff > refSize-references) {
        aff = refSize-references;
      }
      int range = rand() % 10 + 5;
      if (range > pageLimit) {
        range = pageLimit;
      }
      
      char initPage = rand() % (pageLimit-range);
      slocality* temp = (slocality*) malloc(sizeof(slocality));
      if (!temp) {
        printf("Fatal Error: Could not create a new locality.\nQuitting NOW...\n");
        if (v) {
          printf("References: %d\nInitialPage: %d\nRange: %d\nAffinity: %d\n", references, initPage, range, aff);
        }
        exit(-2);
      }
      temp->initialPage = initPage;
      temp->range = range;
      temp->affinity = aff;
      temp->next = head;
      head = temp;
    }
    
    if (v) {
      printf("Locality:\n\tInitialPage: %d\n\tRange: %d\n\tAffinity: %d\n", head->initialPage, head->range, head->affinity);
    }
    
    if (st) {
      genTemporal(&(ref[references]), head->initialPage, head->initialPage + head->range, head->affinity, 0);
    } else {
      int x;
      for (x = 0; x < head->affinity; x++) {
        ref[x+references] = rand() % head->range + head->initialPage;
      }
    }
    
    references += head->affinity;
  }
  
  if (v) {
    printf("Freeing allocated memory\n");
  }
  
  while (head) {
    slocality* temp = head;
    head = head->next;
    free(temp);
  }

  if (v) {
    if (!st) {
      printf("Done with genSpatial()\n");
    } else {
      printf("Done with genSpatialTemporal()\n");
    }
  }
  
}

void genRandom(char* ref, int pageLimit, int refSize, int v) {
  
  if (v) {
    printf("genRandom()\n");
    printf("Randomizing randoms\n");
  }

  const char rft = 'r';
  FILE* rf = fopen("/dev/urandom", &rft);
  char r = fgetc(rf);
  fclose(rf);
  srand(r);
  
  if (v) {
    printf("Generating String\n");
  }

  int x;
  for (x = 0; x < refSize; x++) {
    ref[x] = rand() % pageLimit + 1;
  }

  if (v) {
    printf("Done with genRandom()\n");
  }
}



