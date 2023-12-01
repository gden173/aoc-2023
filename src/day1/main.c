#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCI_ZERO 48
#define ASCI_NINE 57
#define BUFFER_SIZE 256

// Array of strings  to numbers

const char *num_strs[] = {
  "one", "two", 
  "three", "four", "five",
  "six", "seven", "eight", "nine"
};

int num_chars[] = {3, 3, 5, 4, 4, 3, 5, 5, 4};




// Read in the files
FILE * read_file(const char *f) {
  FILE *data_file = fopen(f, "r");
  if (data_file == NULL) {
    fprintf(stderr, "Error opening file %s\n", f);
    exit(EXIT_FAILURE);
  } 
  return data_file;
}




int main(int argc, char **argv) {

  FILE *data_file;
  const char *f;
  if (argc == 1) {
    printf("No file specified\n");
    f = "example.txt";
  } else {
    f = argv[1];
    printf("Reading input: %s\n", f);
  }

  data_file =  read_file(f);

  long value = 0;
  long first_digit = -1;
  long last_digit = -1;

  int iter = -1;
  while (!feof(data_file)) {

    iter++;
    first_digit = -1;
    last_digit = -1;

    char line[BUFFER_SIZE];
    fgets(line, BUFFER_SIZE, data_file);

    int n = strlen(line);

    int i = 0;
    while (i < n) {
      char s = line[i];
      if (s == ' ' || s == '\n' || s == '\0') {
        break;
      }

      if (s >= ASCI_ZERO && s <= ASCI_NINE) {
        if (first_digit < 0) {
          first_digit = s - ASCI_ZERO;
        } else {
          last_digit = s - ASCI_ZERO;
        }
        i++;
      } else {
        int end = i + 4;
        if (end >= n-1) {
          end  = n-1;
        }

        if ((end - i) < 2) {
          i++;
          continue;
        }
        int num = str_to_num(line, i, end);
        if (num > 0) {
          if (first_digit < 0) {
            first_digit = num;
          } else {
            last_digit = num;
          }
          i += num_chars[num-1];
        } else {
          i++;
        }
      }
    }

    if (first_digit < 0) {
      printf("Did not extract first digit correctly\n");
      return EXIT_FAILURE;
    }

    long v = 0;
    if (last_digit >= 0) {
      v += (10 * first_digit + last_digit);
    } else {
      v += (10 * first_digit + first_digit);
    }
    
    if (feof(data_file)) {
      continue;
    }
    value += v;
  }
  printf("Value: %ld\n", value);

  fclose(data_file);
}
