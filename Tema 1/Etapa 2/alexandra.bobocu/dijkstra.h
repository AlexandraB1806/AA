// Bobocu Alexandra-Florentina, 321CA

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_SIZE 20999

int min_distance(int dist[], bool spt_set[], int size);

int dijkstra(int **graph, int **results, int size, int src); 

#endif /* DIJKSTRA_H */
