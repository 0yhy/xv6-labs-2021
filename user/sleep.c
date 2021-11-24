#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  if (argc < 2) {
    write(2, "Missing Argument\n", 18);
    exit(1);
  }
  int second = atoi(argv[1]);
  sleep(second);
  exit(0);
}