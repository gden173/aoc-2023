#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 0x2<<12

// Read in the files
FILE *read_file(const char *f) {
  FILE *data_file = fopen(f, "r");
  if (data_file == NULL) {
    fprintf(stderr, "Error opening file %s\n", f);
    exit(EXIT_FAILURE);
  }
  return data_file;
}

int char_cmp(char *a, char *b) {
  int i = 0;
  while (a[i] != '\0' && b[i] != '\0') {
    if (a[i] != b[i]) {
      return 1;
    }
    i++;
  }
  return 0;
}

int parse_game_id(char *line) {
  int game_id;
  sscanf(line, "Game %d:", &game_id);
  return game_id;
}

int main(int argc, char **argv) {

  FILE *data_file;
  const char *f;
  if (argc == 1) {
    f = "example.txt";
  } else {
    f = argv[1];
  }

  data_file = read_file(f);
  char line[BUFFER_SIZE];
  size_t power_sum = 0;
  while (fgets(line, BUFFER_SIZE, data_file) != NULL) {

    char *ptr = strtok(line, ":");
    int game_id;

    sscanf(ptr, "Game %d", &game_id);
    ptr = strtok(NULL, ",;");
    int vals[3] = {0, 0, 0};
    char *col = malloc(3 * sizeof(char));
    while (ptr != NULL) {
      int val = 0;
      sscanf(ptr, "%d %5c", &val, col);
      if (char_cmp(col, "red") == 0) {
        if (val > vals[0]) {
          vals[0] = val;
        }
      } else if (char_cmp(col, "green") == 0) {
        if (val > vals[1]) {
          vals[1] = val;
        }
      } else if (char_cmp(col, "blue") == 0) {
        if (val > vals[2]) {
          vals[2] = val;
        }
      }
      ptr = strtok(NULL, ";,");
    }

    int psum = vals[0] * vals[1] * vals[2];
    power_sum += (size_t)(psum);
    printf("Game %d: Power Sum %d\n", game_id, psum);
  }
  printf("Power Sum: %zu\n", power_sum);
}
