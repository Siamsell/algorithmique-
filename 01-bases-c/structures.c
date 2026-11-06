/*
 * structures.c : structures imbriquées et tableaux de structures.
 *   - carnet de contacts
 *   - relevé de séismes (durée totale, séisme le plus fort)
 */
#include <stdio.h>

#define MAX 100

typedef struct {
    char nom[30];
    char tel[20];
} Contact;

typedef struct {
    char  nom[20];
    float latitude;
    float longitude;
} Lieu;

typedef struct {
    Lieu  endroit;
    float magnitude;
    int   duree;          /* en secondes */
} Seisme;

void carnet_contacts(void) {
    Contact c[MAX];
    int n;

    printf("Nombre de contacts : ");
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX) return;

    for (int i = 0; i < n; i++) {
        printf("Nom : ");
        scanf("%29s", c[i].nom);
        printf("Telephone : ");
        scanf("%19s", c[i].tel);
    }
    printf("\nListe des contacts :\n");
    for (int i = 0; i < n; i++) printf("  %s : %s\n", c[i].nom, c[i].tel);
}

void releve_seismes(void) {
    Seisme s[MAX];
    int n, total = 0, imax = 0;

    printf("Nombre de seismes : ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) return;

    for (int i = 0; i < n; i++) {
        printf("Seisme %d - lieu latitude longitude magnitude duree : ", i + 1);
        scanf("%19s %f %f %f %d", s[i].endroit.nom, &s[i].endroit.latitude,
              &s[i].endroit.longitude, &s[i].magnitude, &s[i].duree);
        total += s[i].duree;
        if (s[i].magnitude > s[imax].magnitude) imax = i;
    }
    printf("Duree totale : %d s\n", total);
    printf("Seisme le plus fort : %s (magnitude %.1f)\n",
           s[imax].endroit.nom, s[imax].magnitude);
}

int main(void) {
    carnet_contacts();
    printf("\n");
    releve_seismes();
    return 0;
}
