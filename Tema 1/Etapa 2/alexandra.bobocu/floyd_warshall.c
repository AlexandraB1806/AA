// Bobocu Alexandra-Florentina, 321CA

#include "floyd_warshall.h"

// Functia primeste ca parametrii:
// - matricea de adiacenta pe care o voi modifica
// - dimensiunea matricei (numarul de noduri)

// Functia returneaza:
// - 1, daca am putut calcula matricea de adiacenta
// pe baza inputului
// - 0, in caz contrar
int floyd_warshall(int **matrix, int size)
{
	int i, j, k;

	// Trec prin fiecare nod considerand ca este un nod intermediar intre sursa si destinatie
	for (k = 0; k < size; k++) {
        // Aleg toate nodurile ca sursa unul cate unul
        for (i = 0; i < size; i++) {
            // Aleg toate nodurile ca destinatie a sursei alese
            for (j = 0; j < size; j++) {
                if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX &&
                    matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
				}
			}
		}
	}

	// Verific existenta unui ciclu negativ in graf
	for (i = 0; i < size; i++) {
		if (matrix[i][i] < 0) {
			return 1;
		}
	}

	return 0;
}
