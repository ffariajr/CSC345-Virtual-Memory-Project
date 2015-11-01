#include "sim.h"

int v = 0;
int proutput = 0;
int memoutput = 0;
int sysoutput = 0;
int tabular = 0;

int main(int argc, char** argv) {
  
  FILE* inf;
  const char fileReadChar = 'r';

  char loca = 'r';

  if (argc == 2 || argc == 3) {
    if (argc == 3) {
      inf = fopen(argv[2], &fileReadChar);
      if (!strcmp(argv[1], "-v")) {
        v = 1;
      } else if (!strcmp(argv[1], "-mv")) {
        v = 1;
        memoutput = 1;
      } else if (!strcmp(argv[1], "-p")) {
        proutput = 1;
      } else if (!strcmp(argv[1], "-m")) {
        memoutput = 1;
      } else if (!strcmp(argv[1], "-s")) {
        sysoutput = 1;
      } else if (!strcmp(argv[1], "-ts")) {
        tabular = 1;
        sysoutput = 1;
      } else if (!strcmp(argv[1], "-tp")) {
        tabular = 1;
        proutput = 1;
      } else if (!strcmp(argv[1], "-t")) {
        printf("-tp:\nPID\tStart Time\tEnd Time\tSize\tFaults\n\n-ts:\n");
        printf("Run Time\tIdle Time\tProcesses\t");
        printf("Context Switches\tReferences\tPage Faults\tFrames\tReplacement Algorithm\tLocality\n");
        exit(0);
      } else if (!strcmp(argv[1], "-loc-temporal")) {
        tabular = 1;
        sysoutput = 1;
        loca = 't';
      } else if (!strcmp(argv[1], "-loc-spatial")) {
        tabular = 1;
        sysoutput = 1;
        loca = 's';
      } else if (!strcmp(argv[1], "-loc-both")) {
        tabular = 1;
        sysoutput = 1;
        loca = 'b';
      } else if (!strcmp(argv[1], "-loc-random")) {
        tabular = 1;
        sysoutput = 1;
        loca = 'r';
      } else {
        printf("Fatal Error: Invalid Option: %s\nUse %s -h for more information.\n", argv[1], argv[0]);
        exit(-1);
      }
    } else {
      if (!strcmp(argv[1], "-h")) {
        printf("%s [-[m]v | -h | -m | -[t]p | -[t]s | -t] <inputFile>\n\t\t-[m]v\n\t\t\tVerbose output.\n", argv[0]);
        printf("\t\t\tThe option [m] flag outputs the contents of memory after each page\n");
        printf("\t\t\tfault, or memory cleaning after a process terminates.\n");
        printf("\t\t-[t]p\n\t\t\tDisplay summary info on each process termination.\n\t\t\tThe [t] option");
        printf(" indicates that output should be delimetered and in a table format.\n\t\t-m\n\t\t\t");
        printf("Displays memory page request info.\n\t\t");
        printf("-[t]s\n\t\t\tShows summary system info after the system has finished.\n\t\t\tThe [t]");
        printf(" option indicated that output should be delimetered and in a table format.\n\t\t");
        printf("-t\n\t\t\tPrint Table Headers from using Tabular format.\n\t\t<inputFile>");
        printf("\n\t\t\tFile used for input arguments. Must be specified!\n");
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

  int totalIdleTime = 0;
  int totalRunTime = 0;
  int procsExecuted = 0;
  int totalFaults = 0;
  int totalContextSwitches = 0;
  int totalReferences = 0;

  char schedalgo;
  char replalgo;
  int c2forgiveness;
  int tquantum;
  int fullsim;
  int frames;
  char outputFileName[100];
  outputFileName[99] = '\0';
  int startTimes[100];

  char ch = 0;
  int counter = 0;
  while (ch != EOF && counter < 98) {
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
          char num[4];
          num[0] = '\0';
          num[1] = '\0';
          num[2] = '\0';
          num[3] = '\0';
          int q;
          int qlimit = 3;
          for (q = 0; q < qlimit; q++) {
            fscanf(inf, "%c", &ch);
            num[q] = ch;
            if (!validNumber(num)) {
              q--;
              qlimit--;
            }
          }
          if (validNumber(num)) {
            c2forgiveness = atoi(num);
          } else {
            printf("Error: Illegal Input Value for \"Second Chance Forgiveness\": %s\n", num);
          } 
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
          schedalgo = 'r';
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
  if (v) {
    printf("Memory Manager Initialized.\n");
  }

  clok* c = clokInit(tquantum);
  if (v) {
    printf("Simulation System Clock Initialized.\n");
  }


  if (replalgo == '2') {
    c2* datum = (c2*) malloc(sizeof(c2));
    datum->counter = 0;
    datum->forgiveness = c2forgiveness;
    datum->f = &m->allocated;

    event* ec2 = eventInit(&grantChance, datum, 0, 1);
    addEvent(c, ec2);

    if (v) {
      printf("Second Chance Granter Event Registered with Forgiveness: %d.\n", c2forgiveness);
    }
  }


  if (fullsim) {                                                        //part 4
    if (v) {
      printf("Starting Full Simulation.\n");
    }

    sc* s = schedInit(schedalgo, m, c);
    if (v) {
      printf("Scheduler Initialized.\n");
    }
    
    for (q = 0; q < counter; q++) {
      if (startTimes[q] > 0) {
        if (v) {
          printf("Program %d:\n\tStart Time: %d\n\tSize: %d\n", q, startTimes[q], refSizes[q]);
        }
        event* e = ltSchedule(s, refstrings[q], refSizes[q], startTimes[q]);
        addEvent(c, e);
        if (v) {
          printf("Event Created.\n");
        }
      } else if (startTimes[q] == 0) {
        pcbl* p = pcblInit();
        p->node = pcbInit(refstrings[q], refSizes[q]);

        createProcess(s, p);
        if (v) {
          printf("Process %d\n\tSize: %d\n\tPID: %d\n", q, refSizes[q], p->node->pid);
        }
      }
    }

    if (v) {
      printf("%d Programs Scheduled.\n", counter);
    }

    addEvent(c, eventInit(&tqPreempt, s, 0, 0));
    if (v) {
      printf("Time Quantum Preempt Event Set Up.\n");
    }

    s->sched(&s->readyq, &s->runningq);
    totalContextSwitches++;
    if (v) {
      printf("Scheduled Initial Job.\n");
      printf("================================================>  System Running\n");
    }

    while (counter > 0) {
      tick(c);
      if (!((c->time + c->offset) % c->tq)) {
        totalContextSwitches++;
      }
      totalRunTime++;

      pcb* p = 0;
      if (s->runningq) {
        p = s->runningq->node;
      }
      if (v) {
        printf("Time: %d.\n", c->time);
      }
      int term = 0;
      if (s->runningq) {
        term = pcbStep(s->runningq->node);
        if (v) {
          pcb* tempp = s->runningq->node;
          printf("Process:\n\tPID:\t\t%d\n\tSize:\t\t%d\n", tempp->pid, tempp->refSize);
          printf("\tPosition:\t%d\n", tempp->refPosition);
        }
      }
      if (term) {
        procsExecuted++;
        if (v) {
          printf("Current Active Process Finished Execution.\n");
        }
        counter--;
        termActiveProcess(s);
        if (v) {
          printf("Process Terminated.\n");
          if (memoutput) {
            memorySnapshot(m);
          }
        }
        s->sched(&s->readyq, &s->runningq);
        totalContextSwitches++;
        if (v) {
          printf("New Process Scheduled.\n");
        }
        offsetNow(c);
        if (v) {
          printf("Time Quantum Reset.\n");
        }
      } else if (s->runningq) {
        if (v) {
          printf("Process Stepped.\n");
          printf("Requesting Page:\t%d\n", p->currentPage);
        }
        int try = request(m, p);
        totalReferences++;
      
        if (v) {
          printf("Request done.\n");
        }

        if (!try) {
          totalFaults++;
          totalReferences--;
          rollBack(p);

          pcbl* temppcb = s->runningq;
          extract(&s->runningq);
          if (v) {
            printf("Removing Active Process from Running Queue.\n");
          }
          qProcData* tempdata = (qProcData*) malloc(sizeof(qProcData));
          tempdata->start = 6;
          tempdata->counter = 0;
          tempdata->p = temppcb;
          tempdata->s = s;

          addEvent(c, eventInit(&waitingToRunningQWaiter, tempdata, 0, 1));
          if (v) {
            printf("Device Queried for New Page.\n");
            if (memoutput) {
              memorySnapshot(m);
            }
          }
          
          s->sched(&s->readyq, &s->runningq);
          totalContextSwitches++;
          if (v) {
            printf("New Process Scheduled.\n");
          }

          offsetNow(c);
        }
        if (replalgo == 'l') {
          incrementFrames(m->allocated);
        }
      } else {
        if (v) {
          totalIdleTime++;
          printf("No Ready Processes. Programs Still Scheduled.\nBusy Wait.\n");
        }
      }
    }

    if (v) {
      printf("All Processes Terminated.\n");
    }

    schedDestroy(s);
  } else {                                                                      //part 3
  
    if (v) {
      printf("Starting Single Process Simulation.\n");
    }

    pcb* p = pcbInit(refstrings[0], refSizes[0]);
    
    if (v) {
      printf("Single Process PCB Initialized.\n");
    }
    
    loadProcess(m, p);
    
    if (v) {
      printf("New Process Scheduled.\n");
    }

    tick(c);
    totalRunTime++;
    pcbStep(p);
    totalFaults = 0;
    int referencesCount = 1;

    if (v) {
      printf("Now Running!\n");
    }

    while (referencesCount <= p->refSize) {

      if (v) {
        printf("Requesting Page: %d\n", p->currentPage);
        printf("Total References: %d\n", referencesCount);
      } else if (memoutput) {
        printf("Request: %4d\tPage: %3d", referencesCount, p->currentPage);
      }
      int try = request(m, p);
      totalReferences++;
      
      if (v) {
        printf("Request done.\n");
      }

      if (!try) {
        totalReferences--;
        totalFaults++;
        rollBack(p);
        if (v) {
          printf("Begin search for victim page.\n");
        }
        if (memoutput && v) {
          memorySnapshot(m);
        }
        replacement(m, p);
      } else {
        referencesCount++;
      }
      if (replalgo == 'l') {
        incrementFrames(m->allocated);
      }
      tick(c);
      totalRunTime++;
      if (v) {
        printf("Time: %d.\n", c->time);
      }
      pcbStep(p);
    }

    pcbDestroy(p);
  }

  if (v || memoutput) {
    memorySnapshot(m);
  }

  mmDestroy(m);
  if (v) {
    printf("Memory Manager Destroyed.\n");
  }
  clokDestroy(c);
  if (v) {
    printf("Simulation System Clock Destroyed.\n");
  }
  for (q = 0; q < currentRef; q++) {
    free(refstrings[q]);
  }
  if (v) {
    printf("Initial Reference Strings Destroyed.\n");
  }
  if (v) {
    printf("Halt.\n");
  }
  if (v || sysoutput) {
    if (tabular) {
      printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t%d\t\t%d\t%c\t\t\t%c\n", totalRunTime, totalIdleTime, procsExecuted, totalContextSwitches, totalReferences, totalFaults, frames, replalgo, loca);
    } else {
      printf("System Simulation Summary:\n");
      printf("Total Run Time: \t\t%d\n", totalRunTime);
      printf("Total Idle Time: \t\t%d\n", totalIdleTime);
      printf("Processes Executed: \t\t%d\n", procsExecuted);
      printf("Total Context Switches: \t%d\n", totalContextSwitches);
      printf("Total References: \t\t%d\n", totalReferences);
      printf("Total Page Faults: \t\t%d\n", totalFaults);
    }
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

