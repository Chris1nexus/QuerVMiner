#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_CODE  4

/* struct declaration */
typedef struct {
  float x;
  float y;
} point_t;

typedef struct {
  char code[MAX_CODE+1];
  point_t p1;
  point_t p2;
  float area;
  float perimeter;
} rectangle_t;

/* function prototypes */
void file_read (char *, rectangle_t **, int *);
void sort1 (rectangle_t [], int);
void sort2 (rectangle_t [], int);
void save (char *, rectangle_t [], int);

/*
 *  main program
 */
int main (int argc, char *argv[]) {
  rectangle_t *rct;
  int rectangle_num;

  if (argc!=4) {
    fprintf (stderr, "Wrong number of parameter.\n");
    return (1);
  }

  /* open files */
  file_read (argv[1], &rct, &rectangle_num);
  sort1 (rct, rectangle_num);
  save (argv[2], rct, rectangle_num);
  sort2 (rct, rectangle_num);
  save (argv[3], rct, rectangle_num);

  free (rct);
  
  return (EXIT_SUCCESS);
}

/*
 *  rectangle load
 */

void file_read (char *name, rectangle_t **rct, int *num) {
  FILE *fin;
  rectangle_t *vet;
  float x, y, l1, l2;
  int i, n;

  fin = fopen(name, "r");
  if (fin == NULL) {
    fprintf (stderr, "Error opening file.\n");
    exit (0);
  }

  if (fscanf (fin, "%d", &n) == EOF) {
    fprintf (stderr, "Wrong input file format.\n");
    exit (0);
  }

  vet = (rectangle_t *) malloc (n * sizeof (rectangle_t));
  if (vet==NULL) {
    fprintf (stderr, "Memory allocation erro.\n");
    exit (0);
  }

  *num = 0;
  while (fscanf(fin, "%s%f%f", name, &x, &y) != EOF && *num < n) {
    for (i=0; i<*num; i++) 
      if (strcmp(name, vet[i].code) == 0)
        break;
    if (i == *num) {
      /* rectangle NOT found: first point */
      strcpy(vet[i].code, name);
      vet[i].p1.x = x;
      vet[i].p1.y = y;
      *num = *num + 1;
    } else {
      /* rectangle found: second point */
      vet[i].p2.x = x;
      vet[i].p2.y = y;
      l1 = fabs (x - vet[i].p1.x);
      l2 = fabs (y - vet[i].p1.y);
      vet[i].area = l1 * l2;
      vet[i].perimeter = 2 * (l1 + l2);
    }
  }

  fclose(fin);

  *rct = vet;
  
  return;
}

/*
 *  rectangle sorting
 */
void sort1 (rectangle_t rct[], int num_rct) {
  rectangle_t current;
  int i, j;

  for (i=1; i<num_rct; i++) {
    current = rct[i];
    j = i;
    while ((--j >= 0) && (current.area > rct[j].area)) {
      rct[j+1] = rct[j];
    }
    rct[j+1] = current;
  }

  return;
}

/*
 *  rectangle sorting
 */
void sort2 (rectangle_t rct[], int num_rct) {
  rectangle_t current;
  int i, j;

  for (i=1; i<num_rct; i++) {
    current = rct[i];
    j = i;
    while ((--j >= 0) && (current.perimeter > rct[j].perimeter)) {
      rct[j+1] = rct[j];
    }
    rct[j+1] = current;
  }

  return;
}

/*
 *  result display
 */
void save (char *name, rectangle_t rct[], int num_rct) {
  FILE *fout;
  int i;

  fout = fopen (name, "w");
  if (fout == NULL) {
    fprintf (stderr, "Input file not readable!\n");
    return;
  }

  for (i=0; i<num_rct; i++) {
    fprintf (fout, "%s\n", rct[i].code);
  }

  fclose (fout);

  return;
}
