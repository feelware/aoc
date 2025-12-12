#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

uint64_t max(uint64_t a, uint64_t b) {
  return (a > b) ? a : b;
}

uint64_t sum_of_range(uint64_t start, uint64_t end) {
  uint64_t offset = start - 1;
  uint64_t n = end - offset;
  uint64_t top_sum = n * (n + 1) / 2;
  uint64_t base = offset * n;
  return top_sum + base;
}

int sol(FILE *file) {
  char line[256];
  uint64_t total_sum = 0;

  while (fgets(line, sizeof(line), file)) {
    uint64_t start, end;
    sscanf(line, "%lu-%lu", &start, &end);

    char start_str[128], end_str[128];
    sprintf(start_str, "%lu", start);    
    sprintf(end_str, "%lu", end);    

    size_t start_len = strlen(start_str);
    size_t end_len = strlen(end_str);

    printf("%lu (%lu) - %lu (%lu)\n",
      start, start_len,
      end, end_len
    );

    size_t len = start_len;

    while (len <= end_len) {
      if (len % 2) {
        printf("skipping len %lu\n", len);
        len++;
        continue;
      }

      uint64_t half_num_len = len / 2;
      uint64_t repgen = pow(10, half_num_len) + 1;
      uint64_t range_start = pow(10, (half_num_len - 1)) * repgen;
      uint64_t range_end = pow(10, len) - 1;

      if (start > range_start) {
        uint64_t diff = start % repgen;
        range_start = start - diff + repgen;
      }

      if (end < range_end) {
        uint64_t diff = end % repgen;
        range_end = end - diff;
      }
      
      uint64_t half_range_start = range_start / repgen;
      uint64_t half_range_end = range_end / repgen;

      uint64_t range_sum = repgen * sum_of_range(half_range_start, half_range_end);
      total_sum += range_sum;

      printf("repnumbers: %lu - %lu (sum: %lu)\n", range_start, range_end, range_sum);

      len++;
    }

    printf("\n");
  }

  printf("total sum: %lu\n", total_sum);

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
