/*
 * tableaux.c : algorithmes classiques sur les tableaux d'entiers.
 *   - somme, test de tableau binaire
 *   - fusion de deux tableaux triés
 *   - décalage circulaire à droite (récursif)
 */
#include <stdio.h>

void afficher(const int t[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", t[i]);
    printf("\n");
}

int somme(const int t[], int n) {
    int s = 0;
    for (int i = 0; i < n; i++) s += t[i];
    return s;
}

/* Retourne 1 si tous les éléments valent 0 ou 1, 0 sinon. */
int est_binaire(const int t[], int n) {
    for (int i = 0; i < n; i++)
        if (t[i] != 0 && t[i] != 1) return 0;
    return 1;
}

/*
 * Fusionne deux tableaux triés (ordre croissant) A et B dans C.
 * C doit avoir une taille >= na + nb.  Complexité : O(na + nb).
 */
void fusionner(const int A[], int na, const int B[], int nb, int C[]) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb)
        C[k++] = (A[i] <= B[j]) ? A[i++] : B[j++];
    while (i < na) C[k++] = A[i++];
    while (j < nb) C[k++] = B[j++];
}

/* Décale le tableau d'une position vers la droite, `decalage` fois (récursif). */
void decalage_circulaire_droite(int t[], int n, int decalage) {
    if (decalage <= 0 || n <= 1) return;           /* cas de base */

    int dernier = t[n - 1];
    for (int i = n - 1; i > 0; i--) t[i] = t[i - 1];
    t[0] = dernier;

    decalage_circulaire_droite(t, n, decalage - 1);
}

int main(void) {
    int t[]  = {1, 2, 3, 4, 5};
    int b1[] = {0, 1, 1, 0};
    int b2[] = {0, 1, 2};
    int A[]  = {1, 4, 7};
    int B[]  = {2, 3, 9, 10};
    int C[7];

    printf("Somme de t : %d\n", somme(t, 5));
    printf("b1 binaire ? %s\n", est_binaire(b1, 4) ? "oui" : "non");
    printf("b2 binaire ? %s\n", est_binaire(b2, 3) ? "oui" : "non");

    fusionner(A, 3, B, 4, C);
    printf("Fusion : ");
    afficher(C, 7);

    printf("Avant decalage : ");
    afficher(t, 5);
    decalage_circulaire_droite(t, 5, 2);
    printf("Apres decalage de 2 : ");
    afficher(t, 5);
    return 0;
}
