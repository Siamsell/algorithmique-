/*
 * allocation_dynamique.cpp : new / delete, tableau dynamique.
 * Règle : tout `new` doit avoir son `delete` (et `delete[]` pour un tableau).
 */
#include <iostream>
using namespace std;

int main() {
    /* 1. Variables simples allouées sur le tas */
    int   *pi = new int;
    float *pf = new float;
    *pi = 42;
    *pf = 3.14f;
    cout << "*pi = " << *pi << ", *pf = " << *pf << endl;

    delete pi;  pi = nullptr;   // on met le pointeur à nullptr après delete
    delete pf;  pf = nullptr;

    /* 2. Tableau dynamique de taille n choisie à l'exécution */
    int n;
    cout << "Taille du tableau : ";
    if (!(cin >> n) || n <= 0) return 1;

    int *t = new int[n];
    for (int i = 0; i < n; i++) {
        cout << "t[" << i << "] = ";
        cin >> t[i];
    }

    int somme = 0;
    for (int i = 0; i < n; i++) somme += t[i];
    cout << "Somme = " << somme << endl;

    delete[] t;   // libération du tableau
    t = nullptr;  // t ne doit plus être utilisé après ceci
    return 0;
}
