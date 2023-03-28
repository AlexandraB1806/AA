// Bobocu Alexandra-Florentina, 321CA

#ifndef JOHNSON_H
#define JOHNSON_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_SIZE 10999

int min_distance(int dist[], bool spt_set[], int size);

void free_matrix(int **mat, int n);

void dijkstra_for_johnson(int **matrix, int **modified_matrix, int **results, int src, int size);

int bellman_ford(int **matrix, int size, int modify_weights[]);

int johnson(int **matrix, int **results, int size);

#endif /* JOHNSON_H */
