#include <stdio.h>
#include <unistd.h>
#include "tracer.h"

int main(int argc, char ** argv) {
  char **argv2 = &argv[1];
  int exit_code;

  fork_and_trace(argv[1], argc, argv2, "database.sqlite3", &exit_code);

  return exit_code;
}
