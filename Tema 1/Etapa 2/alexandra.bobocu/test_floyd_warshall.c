// Bobocu Alexandra-Florentina, 321CA

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "floyd_warshall.h"

#define NUM_TESTS 1

void free_matrix_floyd(int **mat, int n)
{
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

int main()
{
    int nodes, edges, src, dest, cost;
	int i, j;

	// Aloc spatiu pentru matricea de adiacenta
	int **matrix = malloc(MAX_SIZE * sizeof(*matrix));
    for (int lin = 0; lin < MAX_SIZE; lin++) {
		matrix[lin] = malloc(MAX_SIZE * sizeof(*matrix[lin]));
	}

	FILE *input_file = fopen("test.in", "r");
	FILE *output_file = fopen("test.out", "w");

	for (int file = 0; file < NUM_TESTS; file++) {
		// Citesc din fisierul de intrare numarul de noduri si numarul de muchii
		fscanf(input_file, "%d %d", &nodes, &edges);

		// Initializez matricea de adiacenta
		for (i = 0; i < MAX_SIZE; i++) {
			for (j = 0; j < MAX_SIZE; j++) {
				if (i == j)
					matrix[i][j] = 0;
				else
					matrix[i][j] = INT_MAX;
			}
		}

		for (i = 0; i < edges; i++) {
			// Citesc din fisierul de intrare nodul sursa, nodul destinatie si costul
			// muchiei formate de cele 2 noduri
			fscanf(input_file, "%d %d %d", &src, &dest, &cost);
			// Populez matricea de adiacenta
			matrix[src - 1][dest - 1] = cost;
		}

		clock_t start_t, end_t;
		double elapsed_seconds;

		start_t = clock();
		int err = floyd_warshall(matrix, nodes);
		end_t = clock();

		// Daca graful primit ca input nu poate
		// fi rezolvat de algoritm, iau o variabila
		// separata err care imi indica acest lucru

		// Daca err = 1 -> graful nu este unul rezolvabil
		// Daca err = 0 -> graful se poate rezolva si pot
		// calcula matricea de adiacenta
		if (err == 1) {
			printf("Graf invalid!\n");
			printf("\n");
			fclose(input_file);
			fclose(output_file);
			// Ma duc la urmatorul graf
			continue;
		}
		
		// Daca nu avem eroare, atunci printez matricea
		// de adiacenta in fisierul de output
		for (i = 0; i < nodes; i++) {
			for (j = 0; j < nodes; j++)
				fprintf(output_file, "%d ", matrix[i][j]);
			fprintf(output_file, "\n");
		}

		// Calculez timpul in care algoritmul gaseste drumurile minime
		elapsed_seconds = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    	printf("Timpul de executie in secunde: %f s\n", elapsed_seconds);
		printf("\n");

		fclose(input_file);
		fclose(output_file);
	}

	free_matrix_floyd(matrix, MAX_SIZE);

	return 0;
}
