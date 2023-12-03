#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 0x2 << 12

// Read in the files
FILE *read_file(const char *f) {
  FILE *data_file = fopen(f, "r");
  if (data_file == NULL) {
    fprintf(stderr, "Error opening file %s\n", f);
    exit(EXIT_FAILURE);
  }
  return data_file;
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
  char *col = malloc(1 * sizeof(char));
  int game_id;
  while (fgets(line, BUFFER_SIZE, data_file) != NULL) {

    char *ptr = strtok(line, ":");
    sscanf(ptr, "Game %d", &game_id);

    ptr = strtok(NULL, ",;");
    int vals[3] = {0, 0, 0};

    while (ptr != NULL) {
      int val = 0;
      sscanf(ptr, "%d %1c", &val, col);
      if (col[0] == 'r') {
        if (val > vals[0]) {
          vals[0] = val;
        }
      } else if (col[0] == 'g') {
        if (val > vals[1]) {
          vals[1] = val;
        }
      } else if (col[0] == 'b') {
        if (val > vals[2]) {
          vals[2] = val;
        }
      }
      ptr = strtok(NULL, ";,");
    }

    power_sum += (size_t)(vals[0] * vals[1] * vals[2]);
  }
  printf("%zu\n", power_sum);
  free(col);
}
