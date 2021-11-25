#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  // get process and initial args
  char *process = argv[1];
  char *args[MAXARG] = {0};
  args[0] = process;
  for(int i = 2; i < argc; ++i) {
    args[i - 1] = argv[i];
  }

  char buf[512] = {0};
  char *p = buf;
  // read 1 byte at a time, or there'll be problems
  while(read(0, p, 1)) {
    if(*p == '\n') {
      *p = '\0';
      args[argc - 1] = buf;
      if(fork() == 0) {
        exec(process, args);
      }
      wait((int *) 0);
      p = buf;
      continue;
    }
    ++p;
  }
  exit(0);
}

// echo hello too | xargs echo bye
// sh < xargstest.sh