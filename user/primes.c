#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

const int MAXN = 35;

int
main() {
  int cnt = 0;
  int p[MAXN][2];
  pipe(p[cnt]);
  for(int i = 2; i <= MAXN; ++i) {
    write(p[cnt][1], &i, sizeof i);
  }
  close(p[cnt][1]);

  int x = 0, y = 0;
  while(read(p[cnt][0], &x, sizeof x)) {
    printf("prime %d\n", x);
    if(fork() == 0) {
      pipe(p[++cnt]);
      while(read(p[cnt - 1][0], &y, sizeof y)) {
        if(y % x != 0) {
          write(p[cnt][1], &y, sizeof y);
        }
      }
      close(p[cnt - 1][0]);
      close(p[cnt][1]);
    }
    else {
      wait((int *) 0);
    }
  }
  exit(0);
}