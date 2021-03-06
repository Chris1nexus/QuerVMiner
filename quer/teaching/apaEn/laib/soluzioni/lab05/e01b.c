#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define C 100+2

/* function prototypes */
char **readInput(char *, int *);
void sortDMat(char **, int);
void writeOutput(char *, char **, int);

/*
 *  main program
 */
int main(int argc, char *argv[]) {
  char **dMat;
  int i, num;
 
  if (argc < 3) {
    printf("Error: missing parameter.\n");
    printf("Run as: %s <input_file> <output_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  dMat = readInput(argv[1], &num);
  sortDMat(dMat, num);
  writeOutput(argv[2], dMat, num);

  for (i=0; i<num; i++) {
    free(dMat[i]);
  }
  free(dMat);
  return EXIT_SUCCESS;
} 

/*
 *  load the input file contents
 */
char **readInput(char *name, int *num_ptr) {
  char word[C], **dMat;
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
  dMat = (char **)malloc(n * sizeof(char *));
  if (dMat == NULL) {
    printf("Memory allocation error.\n");
    exit(EXIT_FAILURE);
  }

  /* save the words in the array */
  i = 0;
  while (fscanf(fp, "%s", word) && i<n) {
    dMat[i] = (char *)malloc((strlen(word)+1) * sizeof(char));
    if (dMat[i] == NULL)  {
      printf("Memory allocation error.\n");
      exit(EXIT_FAILURE);
    }
    strcpy(dMat[i], word);
    i++;
  }
  fclose(fp);

  return dMat;
}

/*
 *  insertion sort on (dynamic) dMat
 */
void sortDMat(char **dMat, int num) {
  int i, j;
  char *ptr;

  for (i=1; i<num; i++) {
    ptr = dMat[i];
    j = i;
    while (--j>=0 && strcmp(ptr, dMat[j])<0) {
      dMat[j+1] = dMat[j];
    }
    dMat[j+1] = ptr;
  }
}

/*
 *  write the output file
 */
void writeOutput(char *name, char **dMat, int num) {
  FILE *fp;
  int i;

  fp = fopen(name, "w");
  if (fp == NULL) {
    printf("Error opening the output file.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "%d\n", num);
  for (i=0; i<num; i++) {
    fprintf(fp, "%s\n", dMat[i]);
  }
  fclose(fp);
}
