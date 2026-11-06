/*
 * chaines.c : manipulation de chaînes de caractères (sans <string.h>).
 */
#include <stdio.h>

#define TAILLE_MAX 1000

/* Longueur d'une chaîne. */
int longueur(const char *s) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

/* Copie src dans dest et retourne le nombre de caractères copiés. */
int copier(char *dest, const char *src) {
    int i;
    for (i = 0; src[i] != '\0'; i++) dest[i] = src[i];
    dest[i] = '\0';
    return i;
}

/* Lecture sécurisée d'une ligne (remplace gets(), dangereux). */
void lire_ligne(char *s, int taille) {
    int i;
    if (fgets(s, taille, stdin) == NULL) { s[0] = '\0'; return; }
    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == '\n') { s[i] = '\0'; break; }
}

int main(void) {
    char c[TAILLE_MAX], a[TAILLE_MAX];

    printf("Donner une chaine : ");
    lire_ligne(c, TAILLE_MAX);

    int n = copier(a, c);
    printf("c = \"%s\"\n", c);
    printf("a = \"%s\"\n", a);
    printf("Caracteres copies : %d (longueur de c : %d)\n", n, longueur(c));
    return 0;
}
