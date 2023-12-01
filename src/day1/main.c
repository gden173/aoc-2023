#include <stddef.h>
#include <stdint.h>
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


char *first_char[] = { "on", "tw", "th", "fo", "fi", "si", "se",  "ei", "ni" };

#define NUM_STR_MAP 0x1<<10 
const char *str_map[NUM_STR_MAP];
int  dig_map[NUM_STR_MAP];


// Read in the files
FILE * read_file(const char *f) {
  FILE *data_file = fopen(f, "r");
  if (data_file == NULL) {
    fprintf(stderr, "Error opening file %s\n", f);
    exit(EXIT_FAILURE);
  } 
  return data_file;
}

#define TOKEN_SIZE 0x1<<16
int num[TOKEN_SIZE]; 

int hash(const char s, const char ss) {
  return s + (ss * 20) - 2000;
}


int main(int argc, char **argv) {

for (int i = 0; i < 9; i++) {
    int h = hash(num_strs[i][0], num_strs[i][1]);
    dig_map[h] = i + 1;
    str_map[h] = num_strs[i];
}

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
  char line[BUFFER_SIZE];
  int offset = 0;

  while (fgets(line, BUFFER_SIZE, data_file) != NULL) {
    int i = 0;
    while(i < BUFFER_SIZE) {
      
      char s = line[i];
      if (s == '\n' || s == '\0' || s == ' ') {
        num[offset++] = '\0';
        break;
      }


      if (s >= ASCI_ZERO && s <= ASCI_NINE) {
        num[offset++] = (int)(s - ASCI_ZERO);
         i++;
        continue;
      }


      for (int j = 0; j < 9; j++) {
        if (s == first_char[j][0] && line[i + 1] == first_char[j][1]) {
          int h = hash(s, line[i + 1]);
          const char * v = str_map[hash(s, line[i + 1])];

          int n = strlen(v);
          int k = 0;
          int match = 1;

          while ((k + 2) < n) {


            if (line[i + 2 + k]== '\n' || line[i + 2 +k] == '\0' || line[i+2+k] == ' ') {
              num[offset++] = '\0';
              break;
            }

            if (line[i + 2 + k] != v[k + 2]) {
              match = 0;
              i++;
              break;
            }
          k++;
          }

          if (match == 1) {
            i += n - 1;
            num[offset++] = dig_map[h];
            break;
          }
        }
      }
      i++;
    }
  }


  fclose(data_file);

  size_t size = 0;
  size_t first = 0;
  size_t second = 0;
  for (int i = 0; i < offset; i++) {
    if (num[i] == '\0') {
      if (second == 0) {
        size += 10 * first + first;
        first = 0;
        continue;
      } else {
        size += (10 * first  +  second);
        first = 0;
        second = 0;
        continue;
      }
    }
    if (first == 0) {
      first = num[i];
    } else {
      second = num[i];
    }
  }
 printf("Sum: %zu\n", size);
}
