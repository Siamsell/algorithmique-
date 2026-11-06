/*
 * recursivite.c : fonctions récursives (Fibonacci, inversion d'une chaîne).
 */
#include <stdio.h>
#include <string.h>

/* Fibonacci : F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2). */
int fibonacci(int n) {
    if (n <= 1) return n;                       /* cas de base */
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/* Affiche une chaîne à l'envers, caractère par caractère. */
void afficher_inverse(const char *s) {
    if (*s == '\0') return;                     /* cas de base */
    afficher_inverse(s + 1);
    putchar(*s);
}

int main(void) {
    int n;
    char mot[100];

    printf("Donner n : ");
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    printf("Suite de Fibonacci jusqu'a F(%d) : ", n);
    for (int i = 0; i <= n; i++) printf("%d ", fibonacci(i));

    printf("\nDonner un mot : ");
    if (scanf("%99s", mot) != 1) return 1;
    printf("A l'envers : ");
    afficher_inverse(mot);
    printf("\n");
    return 0;
}
