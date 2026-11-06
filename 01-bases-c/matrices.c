/*
 * matrices.c : produit de deux matrices.
 * C[i][k] = somme sur j de A[i][j] * B[j][k]
 * Le produit n'est possible que si nb colonnes de A == nb lignes de B.
 */
#include <stdio.h>

#define MAX 100

void lire_matrice(int M[MAX][MAX], int lignes, int colonnes, const char *nom) {
    for (int i = 0; i < lignes; i++)
        for (int j = 0; j < colonnes; j++) {
            printf("%s[%d][%d] = ", nom, i, j);
            if (scanf("%d", &M[i][j]) != 1) M[i][j] = 0;
        }
}

void afficher_matrice(int M[MAX][MAX], int lignes, int colonnes) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) printf("%d\t", M[i][j]);
        printf("\n");
    }
}

/* Calcule C = A x B, A de taille n x m, B de taille m x p. */
void produit(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX],
             int n, int m, int p) {
    for (int i = 0; i < n; i++)
        for (int k = 0; k < p; k++) {
            int s = 0;
            for (int j = 0; j < m; j++) s += A[i][j] * B[j][k];
            C[i][k] = s;
        }
}

int main(void) {
    static int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n, m, m2, p;

    printf("Matrice A - lignes n, colonnes m : ");
    if (scanf("%d %d", &n, &m) != 2 || n < 1 || m < 1 || n > MAX || m > MAX) return 1;
    lire_matrice(A, n, m, "A");

    printf("Matrice B - lignes, colonnes : ");
    if (scanf("%d %d", &m2, &p) != 2 || m2 < 1 || p < 1 || m2 > MAX || p > MAX) return 1;
    lire_matrice(B, m2, p, "B");

    if (m != m2) {
        printf("Produit impossible : %d colonnes (A) != %d lignes (B)\n", m, m2);
        return 1;
    }

    produit(A, B, C, n, m, p);
    printf("\nA x B =\n");
    afficher_matrice(C, n, p);
    return 0;
}
