#include <stdio.h>

int sol(FILE *file) {
  char line[256];
  int count = 0;
  int dial = 50;

  while (fgets(line, sizeof(line), file)) {
    char dir;
    int amnt;

    sscanf(line, "%c%d", &dir, &amnt);

    if (dir == 'R') {
      int sum = dial + amnt;
      dial = sum % 100;
    }

    else if (dir == 'L') {
      int inverted_dial = (100 - dial) % 100;
      int sum = inverted_dial + amnt;
      dial = (100 - (sum % 100)) % 100;
    }
    
    else return 1;

    count += (dial == 0) ? 1 : 0;
  }

  printf("count: %d\n", count);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc > 2) return 1;

  char* filename = "input";
  if (argc == 2) filename = argv[1];

  FILE* file = fopen(filename, "r");
  if (file == NULL) return 1;

  int exit_code = sol(file);

  fclose(file);
  return exit_code;
}
