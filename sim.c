#include "sim.h"
#include "2c.h"
#include "clock.h"
#include "fifo.h"
#include "lru.h"
#include "mm.h"
#include "pcbl.h"
#include "proc.h"
#include "rrsched.h"

int main(int argc, char** argv) {
  
  int v = 0;
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
  
  char c = 0;
  int counter = 0;
  while (c != EOF) {
    fscanf(inf, "%c", &c);
    if (c == ':') {
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
        strcmp(s, outputFileName);
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
            c = EOF;
          }
        }
      }
    }
  }
  
  if (v) {
    printf("Input File processed.\n");
  }

  counter = counter - 6;
  if (counter < 1) {
    printf("Error: Illegal Amount of Reference Strings: %d\n", counter);
    exit(-2);
  }

  fclose(inf);

  FILE* refs = fopen(outputFileName, fileReadChar); 
  if (!refs) {
    printf("Fatal Error: Could not open reference string file: %s\n", outputFileName);
    exit(-2);
  }

  pcbl new;
  pcbl 


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
