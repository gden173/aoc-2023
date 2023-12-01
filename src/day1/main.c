#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCI_ZERO 48
#define ASCI_NINE 57
#define BUFFER_SIZE 256

// Read in the files
FILE *read_file(const char *f) {
  FILE *data_file = fopen(f, "r");
  if (data_file == NULL) {
    fprintf(stderr, "Error opening file %s\n", f);
    exit(EXIT_FAILURE);
  }
  return data_file;
}

#define TOKEN_SIZE 0x1 << 16
int num[TOKEN_SIZE];


bool is_null_char(const char s) {
  return  s == '\0' || s == '\n' || s == ' '; 
}

bool is_digit(const char s) { return s >= ASCI_ZERO && s <= ASCI_NINE; }

int main(int argc, char **argv) {

  FILE *data_file;
  const char *f;
  if (argc == 1) {
    f = "day1_input.txt";
  } else {
    f = argv[1];
  }

  data_file = read_file(f);

  char line[BUFFER_SIZE];

  int offset = 0;

  while (fgets(line, BUFFER_SIZE, data_file) != NULL) {

    int i = 0;
    while( i < BUFFER_SIZE && line[i] != '\0') {
      char s = line[i];

      if (is_null_char(s)) {
        num[offset++] = '\0';
        break;
      }

      if (is_digit(s)) {
        num[offset++] = (int)(s - ASCI_ZERO);
        i++;
        continue;
      }

      const char *ss;
      int var = 0;
      switch (s) {
      case 'o':
        ss = "one";
        var = 1;
        break;
      case 't':
        if (line[i + 1] == 'w') {
          ss = "two";
          var = 2;
        } else {
          ss = "three";
          var = 3;
        }
        break;
      case 'f':
        if (line[i + 1] == 'o') {
          ss = "four";
          var = 4;
        } else {
          ss = "five";
          var = 5;
        }
        break;
      case 's':
        if (line[i + 1] == 'i') {
          ss = "six";
          var = 6;
        } else {
          ss = "seven";
          var = 7;
        }
        break;
      case 'e':
        ss = "eight";
        var = 8;
        break;
      case 'n':
        ss = "nine";
        var = 9;
        break;
      }

      int match = 1;
      for (int j = 0; j < strlen(ss); j++) {
        if (ss[j] != line[i + j]) {
          match = 0;
          i++;
          break;
        }
      }

      if (match == 1) {
        num[offset++] = var;
        i += strlen(ss) - 1;
      }
    }
  }

  fclose(data_file);

  size_t size = 0;
  size_t idx = 0;
  size_t iidx = -1;

  for (int i = 0; i < offset; i++) {
    if (num[i] == '\0') {
      idx = i;
      size += (num[iidx + 1] * 10 + num[idx - 1]);
      iidx = idx;
    }
  }

  size += (num[idx + 1] * 10 + num[offset - 1]);
  printf("Total size: %zu\n", size);
}
