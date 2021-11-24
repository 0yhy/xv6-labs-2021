#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main() {
  int p1[2], p2[2];
  pipe(p1);
  pipe(p2);
  // child process
  if(fork() == 0) {
    char buf[1];
    read(p1[0], buf, 1);
    close(p1[0]);
    int pid = getpid();
    printf("%d: received ping\n", pid);
    write(p2[1], "i", 1);
    close(p2[1]);
    exit(0);
  }
  // parent process
  else {
    write(p1[1], "o", 1);
    close(p1[1]);
    char buf[1];
    read(p2[0], buf, 1);
    close(p2[0]);
    int pid = getpid();
    printf("%d: received pong\n", pid);
    exit(0);
  }
}