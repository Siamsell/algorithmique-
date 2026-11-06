/*
 * fonctions.c : fonctions simples (max, min, signe, parité, divisibilité).
 */
#include <stdio.h>

int maximum(int a, int b) { return (a > b) ? a : b; }
int minimum(int a, int b) { return (a < b) ? a : b; }

/* Retourne 1 si a et b sont non nuls et de même signe, 0 sinon. */
int meme_signe(int a, int b) {
    return (a > 0 && b > 0) || (a < 0 && b < 0);
}

int est_pair(int n) { return n % 2 == 0; }

/*
 * Teste si b divise a par soustractions successives (sans utiliser % ni /).
 * Hypothèses : a >= 0 et b > 0.
 */
int divise(int a, int b) {
    if (a < 0 || b <= 0) return 0;
    while (a >= b) a -= b;
    return a == 0;
}

int main(void) {
    int a, b;
    printf("Donner a et b : ");
    if (scanf("%d %d", &a, &b) != 2) return 1;

    printf("max = %d, min = %d\n", maximum(a, b), minimum(a, b));
    printf("a et b %s le meme signe\n", meme_signe(a, b) ? "ont" : "n'ont pas");
    printf("a est %s, b est %s\n", est_pair(a) ? "pair" : "impair",
                                    est_pair(b) ? "pair" : "impair");
    printf("b %s a\n", divise(a, b) ? "divise" : "ne divise pas");
    return 0;
}
