// Bobocu Alexandra-Florentina, 321CA

#include "dijkstra.h"

// Functie ajutatoare pentru gasirea nodului cu valoarea
// distantei minime dintre nodurile care nu au fost
// deja incluse in SPT (Shortest Path Tree)

// Functia returneaza -1 daca nu am gasit nodul,
// sau nodul in caz contrar
int min_distance(int dist[], bool spt_set[], int size) 
{
	int min = INT_MAX, min_index = -1; 
	for (int v = 0; v < size; v++) {
		// Algoritmul Dijkstra nu functioneaza
		// pe grafuri cu cost negativ
		if (dist[v] < 0) {
			min_index = -1;
			break;
		}
		if (spt_set[v] == false && dist[v] <= min) {
			min = dist[v];
            min_index = v;
        }
    }

	return min_index; 
} 

// Functia primeste ca parametrii:
// - matricea de adiacenta
// - matricea de adiacenta (matricea rezultat) dupa modificari
// - nodul sursa; se calculeaza calea cea mai scurta pana la oricare alt nod
// din graf

// Functia returneaza:
// - 1, daca am putut calcula matricea de adiacenta
// pe baza inputului
// - 0, in caz contrar
int dijkstra(int **matrix, int **results, int size, int src)
{
    // Vectorul ce va fi returnat si va contine distanta minima intre
    // nodul sursa si orice alt nod
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
		// Alegem nodul de distanta minima din setul de noduri
        // care inca nu au fost vizitate
        // u = src la prima iteratie
		int u = min_distance(dist, spt_set, size); 
		if (u == -1) {
			printf("Graf invalid!\n");
			printf("\n");
			return 1;
		}

		// Marcam nodul aflat ca fiind procesat
		spt_set[u] = true; 

        // Actualizam valoarea distantei intre nodul curent si nodurile vecine
		for (int v = 0; v < size; v++) {
			// Schimbam valoarea lui dist[v] doar daca nodul nu a fost vizitat, daca
        	// exista o muchie intre nodul u care tocmai a fost vizitat si v
        	// si daca costul drumului de la src la v prin u este mai mic decat
        	// valoarea curenta din dist[v]
			if (spt_set[v] == false && matrix[u][v] != INT_MAX && dist[u] != INT_MAX
				&& dist[u] + matrix[u][v] < dist[v])
				dist[v] = dist[u] + matrix[u][v]; 
		}
	}

	// Copiez distantele intre sursa si celelalte noduri
	// intr-o matrice care imi retine rezultatul
	for (int i = 0; i < size; i++)
		results[src][i] = dist[i];

	return 0;
}
