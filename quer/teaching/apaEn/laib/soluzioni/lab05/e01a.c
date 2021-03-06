#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define C 100+2

typedef struct string_s {
  char *str;
} string_t;

/* function prototypes */
string_t *readInput(char *, int *);
void sortDMat(string_t *, int);
void writeOutput(char *, string_t *, int);

/*
 *  main program
 */
int main(int argc, char *argv[]) {
  string_t *v;
  int i, num;
 
  if (argc < 3) {
    printf("Error: missing parameter.\n");
    printf("Run as: %s <input_file> <output_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  v = readInput(argv[1], &num);
  sortDMat (v, num);
  writeOutput (argv[2], v, num);

  for (i=0; i<num; i++) {
    free (v[i].str);
  }
  free(v);
  
  return EXIT_SUCCESS;
} 

/*
 *  load the input file contents
 */
string_t *readInput(char *name, int *num_ptr) {
  char word[C];
  string_t *v;
  int n, i;
  FILE *fp;

  /* count the words */
  fp = fopen(name, "r");
  if (fp == NULL) {
    printf("Error opening the file %s.\n", name);
    exit(EXIT_FAILURE);
  }

  if (fscanf(fp, "%d", &n) == EOF) {
    printf("Error opening the file %s.\n", name);
    exit(EXIT_FAILURE);
  }
  *num_ptr = n;

  /* allocate data structure */
  v = (string_t *) malloc (n * sizeof (string_t));
  if (v == NULL) {
    fprintf (stderr, "Memory allocation error.\n");
    exit(EXIT_FAILURE);
  }

  /* save the words in the array */
  i = 0;
  while (fscanf(fp, "%s", word) && i<n) {
    v[i].str = (char *) malloc ((strlen(word)+1) * sizeof(char));
    if (v[i].str == NULL)  {
      fprintf (stderr, "Memory allocation error.\n");
      exit (EXIT_FAILURE);
    }
    strcpy (v[i].str, word);
    i++;
  }
  fclose(fp);

  return v;
}

/*
 *  insertion sort on (dynamic) dMat
 */
void sortDMat(string_t *v, int num) {
  int i, j;
  char *ptr;

  for (i=1; i<num; i++) {
    ptr = v[i].str;
    j = i;
    while (--j>=0 && strcmp(ptr, v[j].str)<0) {
      v[j+1].str = v[j].str;
    }
    v[j+1].str = ptr;
  }

  return;
}

/*
 *  write the output file
 */
void writeOutput(char *name, string_t *v, int num) {
  FILE *fp;
  int i;

  fp = fopen(name, "w");
  if (fp == NULL) {
    printf("Error opening the output file.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "%d\n", num);
  for (i=0; i<num; i++) {
    fprintf(fp, "%s\n", v[i].str);
  }
  
  fclose(fp);

  return;
}
