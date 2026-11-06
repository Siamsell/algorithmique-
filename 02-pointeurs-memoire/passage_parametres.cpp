/*
 * passage_parametres.cpp : les trois modes de passage de paramètres en C++
 *   - par valeur     : la fonction travaille sur une copie
 *   - par adresse    : la fonction reçoit un pointeur
 *   - par référence  : la fonction reçoit un alias de la variable
 * + quelques algorithmes écrits avec des pointeurs.
 */
#include <iostream>
using namespace std;

void incrementer_valeur(int x)    { x = x + 1; }   /* l'appelant ne voit rien */
void incrementer_adresse(int *x)  { *x = *x + 1; }
void incrementer_reference(int &x){ x = x + 1; }

void echanger(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Écrit le maximum de *x et *y dans *max. */
void maximum(const int *x, const int *y, int *max) {
    *max = (*x < *y) ? *y : *x;
}

/* Retourne l'indice du plus petit élément du tableau t de taille n. */
int indice_min(const int *t, int n) {
    int imin = 0;
    for (int i = 1; i < n; i++)
        if (t[i] < t[imin]) imin = i;
    return imin;
}

int main() {
    int a = 10;

    incrementer_valeur(a);
    cout << "Apres passage par valeur    : a = " << a << endl;   // 10
    incrementer_adresse(&a);
    cout << "Apres passage par adresse   : a = " << a << endl;   // 11
    incrementer_reference(a);
    cout << "Apres passage par reference : a = " << a << endl;   // 12

    int x = 3, y = 8, max;
    echanger(&x, &y);
    cout << "Apres echange : x = " << x << ", y = " << y << endl;
    maximum(&x, &y, &max);
    cout << "Maximum : " << max << endl;

    int t1[] = {7, 3, 9, 1, 5};
    int t2[] = {4, 8, 2, 6};
    int i1 = indice_min(t1, 5), i2 = indice_min(t2, 4);
    cout << "Min de t1 : " << t1[i1] << " (indice " << i1 << ")" << endl;
    cout << "Min de t2 : " << t2[i2] << " (indice " << i2 << ")" << endl;

    /* On échange les deux minimums entre les tableaux. */
    echanger(&t1[i1], &t2[i2]);
    cout << "Apres echange des minimums : t1[" << i1 << "] = " << t1[i1]
         << ", t2[" << i2 << "] = " << t2[i2] << endl;
    return 0;
}
