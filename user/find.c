#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void
find(char *dir, char *name) {
  struct dirent de;
  int fd = open(dir, 0);

  // read all files in current directory
  while(read(fd, &de, sizeof de) == sizeof de) {
    // dir + current file name
    char buf[512] = {0}, *p;
    memmove(buf, dir, strlen(dir));
    p = buf + strlen(buf);
    *p++ = '/';
    memmove(p, de.name, strlen(de.name));

    // compare current file name and the name we're finding
    if(strcmp(name, de.name) == 0) {
      printf("%s/%s\n", dir, name);
    }

    struct stat st;
    stat(buf, &st);
    if(st.type == T_DIR && strcmp(".", de.name) && strcmp("..", de.name)) {
      find(buf, name);
    }
  }
  close(fd);
}

int
main(int argc, char *argv[]) {
  find(argv[1], argv[2]);
  exit(0);
}

