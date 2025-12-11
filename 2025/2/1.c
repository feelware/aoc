#include <stdio.h>
#include <string.h>

int sol(FILE *file) {
  char line[256];

  while (fgets(line, sizeof(line), file)) {
    unsigned start, end;
    sscanf(line, "%u-%u", &start, &end);
    
    char start_str[128], end_str[128];
    sprintf(start_str, "%u", start);    
    sprintf(end_str, "%u", end);    

    size_t start_len = strlen(start_str);
    size_t end_len = strlen(end_str);

    // printf("%u (%lu) - %u (%lu)\n",
    //   start, start_len,
    //   end, end_len
    // );

    size_t cur_len = start_len;

    while (cur_len <= end_len) {
      if (cur_len % 2) continue;
      
      /*
        - find shortest repnumber greater than start (right-adjacent)
        - find largest repnumber less than end (left-adjacent)
        - compute sum of repnumbers within range

        ---

        to find repnumbers adjacent to a certain number
        compute "number % repgen"

        remember that:
        
        "any repnumber % repgen" = 0
        55 % 11 = 0
        2323 % 101 = 0
        567567 % 1001 = 0

        "x (any number) % repgen" = distance between x and left-adjacent repnumber
        57 % 11 = 2
        2333 % 101 = 10
        567570 % 1001 = 3

        repnumber / repgen = number that repeats within repnumber
        55 / 11 = 5
        2323 / 101 = 23
        567567 / 1001 = 567
      */

      cur_len++;
    }
  }

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
