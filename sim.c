#include "sim.h"

int v = 0;

int main(int argc, char** argv) {
  
  FILE* inf;
  const char fileReadChar = 'r';

  if (argc == 2 || argc == 3) {
    if (argc == 3) {
      inf = fopen(argv[2], &fileReadChar);
      if (!strcmp(argv[1], "-v")) {
        v = 1;
      } else {
        printf("Fatal Error: Invalid Option: %s\nUse %s -h for more information.\n", argv[1], argv[0]);
        exit(-1);
      }
    } else {
      if (!strcmp(argv[1], "-h")) {
        printf("%s [-v] <inputFile>\n\t\t-v\n\t\t\tVerbose output.\n\t\t<inputFile>\n\t\t\t", argv[0]);
        printf("File used for input arguments. Must be specified!\n");
        exit(0);
      }
      inf = fopen(argv[1], &fileReadChar);
    }

    if (!inf) {
      printf("Fatal Error: Could not open input file.\n");
      exit(-1);
    }
  } else {
    printf("Fatal Error: Invalid amount of arguments.\nUse %s -h for help.\n", argv[0]);
    exit(-1);
  }

  if (v) {
    printf("Input File Open.\n");
  }
 
  char sched;
  char replalgo;
  int tquantum;
  int fullsim;
  int frames;
  char outputFileName[100];
  outputFileName[99] = '\0';
  int startTimes[100];
  
  char ch = 0;
  int counter = 0;
  while (ch != EOF) {
    fscanf(inf, "%c", &ch);
    if (ch == ':') {
      char s[100];
      fscanf(inf, "%100s", s);
      s[99] = '\0';
      if (counter == 0) {
        if (v) {
          printf("Run Full Simulation input\n");
        }
        if (!strcmp(s, "YES")) {
          fullsim = 1;
        } else if (!strcmp(s, "NO")) {
          fullsim = 0;
        } else {
          printf("Error: Illegal Input Value for \"Run Full Simulation\": %s\n", s);
          exit(-2);
        }
        counter++;
      } else if (counter == 1) {
        if (v) {
          printf("Replacement Algorithm input\n");
        }
        if (!strcmp(s, "FIFO")) {
          replalgo = 'f';
        } else if (!strcmp(s, "LRU")) {
          replalgo = 'l';
        } else if (!strcmp(s, "2C")) {
          replalgo = '2';
        } else {
          printf("Error: Illegal Input Value for \"Replacement Algorithm\": %s\n", s);
          exit(-2);
        }
        counter++;
      } else if (counter == 2) {
        if (v) {
          printf("Time Quantum input\n");
        }
        if (validNumber(s)) {
          tquantum = atoi(s);
        } else {
          printf("Error: Illegal Input Value for \"Time Quantum\": %s\n", s);
          exit(-2);
        }
        counter++;
      } else if (counter == 3) {
        if (v) {
          printf("Memory Frames input\n");
        }
        if(validNumber(s)) {
          frames = atoi(s);
        } else {
          printf("Error: Illegal Input Value for \"Memory Frames\": %s\n", s);
          exit(-2);
        }
        counter++;
      } else if (counter == 4) {
        if (v) {
          printf("Scheduler input\n");
        }
        if (!strcmp(s, "RR")) {
          sched = 'r';
        } else {
          printf("Error: Illegal Input Value for \"Scheduler\": %s\n", s);
        }
        counter++;
      } else if (counter == 5) {
        if (v) {
          printf("Reference String File input\n");
        }
        strcpy(outputFileName, s);
        counter++;
      } else if (counter > 5) {
        if (v) {
          printf("Reference String Start Time input\n");
        }
        if (validNumber(s)) {
          int val = atoi(s);
          if (val >= 0) {
            startTimes[counter-6] = val;
            counter++;
          } else {
            ch = EOF;
          }
        }
      }
    }
  }

  fclose(inf);
  
  if (v) {
    printf("Input File processed.\n");
  }

  counter = counter - 6;
  if (counter < 1 || (counter > 99 && fullsim) || (counter > 1 && !fullsim)) {
    if (fullsim) {
      printf("Error: Illegal Amount of Reference Strings for Full Simulation: %d\n", counter);
    } else {
      printf("Error: Illegal Amount of Reference Strings for Single Process: %d\n", counter);
    }
    exit(-2);
  }

  FILE* refs = fopen(outputFileName, &fileReadChar); 
  if (!refs) {
    printf("Fatal Error: Could not open reference string file: %s\n", outputFileName);
    exit(-2);
  }

  if (v) {
    printf("Loading Reference Strings.\n");
  }

  char refc = fgetc(refs);
  int refSizes[99];
  int q;
  for (q = 0; q < 99; q++) {
    refSizes[q] = 0;
  }
  char* refstrings[99];
  for (q = 0; q < 99; q++) {
    refstrings[q] = 0;
  }
  int currentRef = 0;
  int currentBuffer = 0;


  while (refc != EOF) {
    if (v) {
      printf("Loading a new string.\n");
    }
    while (refc != ~0) {
      refSizes[currentRef]++;
      if (refSizes[currentRef] > currentBuffer) {
        if (v) {
          printf("Making new buffer.\n");
        }
        
        char* temp = (char*) malloc(sizeof(char) * (currentBuffer + 50));
        if (v) {
          printf("Copying old buffer to new buffer.\n");
        }

        if (!refstrings[currentRef]) {
          refstrings[currentRef] = temp;
        } else {
          memcpy(temp, refstrings[currentRef], currentBuffer);
          char* temp2 = temp;
          temp = refstrings[currentRef];
          refstrings[currentRef] = temp2;
          free(temp);
        }
        currentBuffer += 50;
        if (v) {
          printf("Done making new buffer.\n");
        }
      }
      refstrings[currentRef][refSizes[currentRef]-1] = refc;
      refc = fgetc(refs);
    }
    if (v) {
      printf("Done loading string:\n%s\n", refstrings[currentRef]);
    }
    currentBuffer = 0;
    currentRef++;
    refc = fgetc(refs);
  }
  fclose(refs);

  if (counter > currentRef) {
    printf("Error: Too Few Reference Strings Loaded:\nReference Strings in Input File: %d\n", counter);
    printf("Reference Strings in Reference Strings File: %d\n", currentRef);
    exit(-2);
  }

  if (v) {
    printf("Reference Strings Loaded Successfully!\n");
  }
  
  mm* m = mmInit(replalgo, frames);
  clok* c = clokInit(tquantum);

  if (v) {
    printf("Memory Manager Initialized.\n");
  }

  if (fullsim) {
    if (v) {
      printf("Starting Full Simulation.\n");
    }
    if (v) {
      printf("Simulation System Clock Initialized.\n");
    }
    //part 4

  } else {
    //part 3

    if (v) {
      printf("Starting Single Process Simulation.\n");
    }
    if (v) {
      printf("Clock Initialized.\n");
    }

    pcb* p = pcbInit(refstrings[0], refSizes[0]);
    
    if (v) {
      printf("Single Process PCB Initialized.\n");
    }
    
    createProcess(m, p);
    
    if (v) {
      printf("New Process Scheduled.\n");
    }

    if (replalgo == '2') {
      c2* datum = (c2*) malloc(sizeof(c2));
      datum->counter = 0;
      datum->f = &m->allocated;

      event* ec2 = eventInit(&grantChance, datum, 1, 0, 1);
      addEvent(c, ec2);

      if (v) {
        printf("Second Chance Granter Event Registered.\n");
      }
    }


    tick(c);
    char page = pcbStep(p);
    int faults = 0;
    int referencesCount = 1;

    if (v) {
      printf("Now Running!\n");
    }

    while (referencesCount <= p->refSize) {

      memorySnapshot(m);

      if (v) {
        printf("Requesting Page: %d\n", page);
        printf("Total References: %d\n", referencesCount);
      } else {
        printf("Request: %4d\tPage: %3d", referencesCount, page);
      }
      int try = request(m, p);
      
      if (v) {
        printf("Request done.\n");
      }

      if (!try) {
        faults++;
        rollBack(p);
        if (v) {
          printf("Begin search for victim page.\n");
        }
        replacement(m, p);
      } else {
        referencesCount++;
      }
      if (replalgo == 'l') {
        incrementFrames(m->allocated);
      }
      tick(c);
      page = pcbStep(p);
    }

    pcbDestroy(p);
  }

  if (v) {
    memorySnapshot(m);
  }

  mmDestroy(m);
  clokDestroy(c);
  for (q = 0; q < currentRef; q++) {
    free(refstrings[q]);
  }
}

int validNumber(char* s) {
  char c = s[0];
  int x = 1;
  if (c == '-') {
    x = 2;
    c = s[1];
  }
  int valid = 1;
  while (c != '\0' && valid) {
    if (c < '0' || c > '9') {
      valid = 0;
    }
    c = s[x];
    x++;
  }

  return valid;
}

void memorySnapshot(mm* m) {
  if (v) {
    printf("Memory Snapshot:\n");
    frame* temp = m->allocated;
    int q;
    for (q = 0; q < 2; q++) {
      while (temp) {
        if (!q) {
          printf("Allocated ");
        } else {
          printf("Free ");
        }
        printf("[ < %4d , %3d > , %5d ]\n", temp->pid, temp->page, temp->lastUsed);
        temp = temp->next;
      }
      temp = m->freemem;
    }
  }
}

