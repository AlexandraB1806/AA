// Bobocu Alexandra-Florentina, 321CA

#include "johnson.h"

// Functie ajutatoare pentru gasirea nodului cu valoarea
// distantei minime dintre nodurile care nu au fost
// deja incluse in SPT (Shortest Path Tree)

// Functia returneaza -1 daca nu am gasit nodul,
// sau nodul in caz contrar
int min_distance(int dist[], bool spt_set[], int size) 
{
	int min = INT_MAX, min_index = -1; 
	for (int v = 0; v < size; v++) {
		if (spt_set[v] == false && dist[v] <= min) {
			min = dist[v];
            min_index = v;
        }
    }
	return min_index; 
} 

void free_matrix(int **mat, int n)
{
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

// Aplic algoritmul Dijkstra pentru Johnson
// Algoritmul va fi aplicat pe o matrice
// cu costuri pozitive, deoarece algoritmul Bellman-Ford
// rulat inainte ne asigura ca nu avem costuri negative
void dijkstra_for_johnson(int **matrix, int **copy_mat, int **results, int src, int size)
{
	// Vectorul ce va fi returnat si va contine distanta minima
	// intre nodul sursa si celelealte noduri
	int dist[size];

	// Vectorul are valoarea true daca am calculat distanta minima
    // de la nodul sursa la orice alt nod sau daca nodul la care
    // ajungem este deja inclus in SPT
	bool spt_set[size];

    // Initializez toate distantele ca fiind INT_MAX
    // Initializez vectorul de vizite cu false
	for (int i = 0; i < size; i++) {
		dist[i] = INT_MAX;
        spt_set[i] = false;
    }

	// Distanta intre sursa si ea insasi este mereu 0
	dist[src] = 0;

    // Calculez distanta minima intre sursa si celelalte noduri
	// Iterez prin lista nodurilor ramase
	for (int count = 0; count < size - 1; count++) {
		// Alegem varful de distanta minima dintre setul de noduri
        // care inca nu au fost vizitate
        // u = src la prima iteratie
		int u = min_distance(dist, spt_set, size); 

		// Marcam nodul aflat ca fiind procesat
		spt_set[u] = true; 

        // Actualizam valoarea distantei intre nodul curent si nodurile vecine
		for (int v = 0; v < size; v++) {
            // Schimbam valoarea lui dist[v] doar daca nodul nu a fost vizitat, daca
            // exista o muchie intre nodul u care tocmai a fost vizitat si v
            // si daca costul drumului de la src la v prin u este mai mic decat
            // valoarea curenta din dist[v]
			if (spt_set[v] == false && matrix[u][v] != INT_MAX && dist[u] != INT_MAX
				&& dist[u] + copy_mat[u][v] < dist[v]) 
				dist[v] = dist[u] + copy_mat[u][v];
        } 
	}

	// Copiez distantele intre sursa si celelalte noduri
	// intr-o matrice care imi retine rezultatul
	for (int i = 0; i < size; i++)
		results[src][i] = dist[i];
}

// Functie care calculeaza distanta minima dintre sursa si toate celelalte
// noduri folosind algoritmul Bellman-Ford

// Functia primeste ca parametrii:
// - matricea de adiacenta
// - numarul de noduri
// - vector care contine costurile recalculate astfel incat sa fie nenegative

// Functia returneaza:
// - 1, daca avem graf cu ciclu negativ
// - 0, in caz contrar
int bellman_ford(int **matrix, int size, int modify_weights[]) {

	// Se adauga un nou nod in graf
    int dist[size + 1];

	// Initializez distantele tuturor nodurilor
	for (int i = 0; i < size; i++) {
		dist[i] = INT_MAX;
    }

	// Distanta intre sursa si ea insasi este mereu 0
    dist[size] = 0;

	for(int i = 0; i < size; i++)
		matrix[size][i] = 0;

	// Relaxarea muchiilor
	// O cale scurta de la nodul sursa la orice alt nod
	// poate avea (|V| - 1) muchii
    for (int count = 0; count < size - 1; count++) {
        for (int i = 0; i <= size; i++) {
            for (int j = 0; j <= size; j++) {
                if (dist[i] != INT_MAX && dist[i] + matrix[i][j] < dist[j]) {
                    dist[j] = dist[i] + matrix[i][j];
                }  
            }
        }
    }
	
	// Verificarea existentei ciclurilor cu cost negativ
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (dist[i] != INT_MAX && dist[i] + matrix[i][j] < dist[j]) {
				return 1;
            }  
        }
    }

    for (int i = 0; i < size; i++)
		modify_weights[i] = dist[i];
	
	return 0;
}

// Functia primeste ca parametrii:
// - matricea de adiacenta
// - matricea de adiacenta (matricea rezultat) dupa modificari
// - dimensiunea matricei (numarul de noduri)

// Functia returneaza:
// - 1, daca am putut calcula matricea de adiacenta
// pe baza inputului
// - 0, in caz contrar
int johnson(int **matrix, int **results, int size) {
	// Vectorul cu costurile muchiilor modificate
	// Am dimensiunea size + 1 deoarece
	// am mai adaugat un nod in graf pe care il conectez
	// la celelealte noduri prin muchii cu costul 0
	int modify_weights[size + 1];

	// Aplic algoritmul Bellman-Ford pentru a
	// recalcula costurile muchiilor pe noul graf.
	// In urma acestui pas, costurile muchiilor
	// devin nenegative
	int err = bellman_ford(matrix, size, modify_weights);
	if (err == 1) {
		printf("Graf invalid!\n");
		printf("\n");
		return 1;
	}

	// Aloc spatiu pentru o noua matrice
	int **modified_matrix = malloc(MAX_SIZE * sizeof(*modified_matrix));
    for (int lin = 0; lin < MAX_SIZE; lin++) {
		modified_matrix[lin] = malloc(MAX_SIZE * sizeof(*modified_matrix[lin]));
	}

	// O initializez
	for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
			if (i == j)
				modified_matrix[i][j] = 0;
			else
				modified_matrix[i][j] = INT_MAX;
        }
	}

	// Modific costurile astfel incat sa nu existe costuri negative
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			modified_matrix[i][j] = matrix[i][j] + modify_weights[i] - modify_weights[j];
		}
	}
	
	int **copy_mat = malloc(MAX_SIZE * sizeof(*copy_mat));
    for (int lin = 0; lin < MAX_SIZE; lin++) {
		copy_mat[lin] = malloc(MAX_SIZE * sizeof(*copy_mat[lin]));

	}
	
	for (int lin = 0; lin < size; lin++)
		for (int col = 0; col < size; col++)
			copy_mat[lin][col] = 0;

	// Aplic algoritmul Dijkstra pe fiecare muchie
	// ce a fost construita de la nodul adaugat in plus
	for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
        	for(int k = 0; k < size; k++) {
				copy_mat[j][k] = modified_matrix[j][k];
            }
		}
        dijkstra_for_johnson(matrix, copy_mat, results, i, size);
	}

	free_matrix(modified_matrix, MAX_SIZE);
	free_matrix(copy_mat, MAX_SIZE);

	return 0;
}
