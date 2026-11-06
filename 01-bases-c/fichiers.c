/*
 * fichiers.c : gestion de fichiers (texte et binaire) avec une structure.
 *   Partie 1 (texte)   : création, lecture + moyenne générale, ajout
 *   Partie 2 (binaire) : insertion d'un enregistrement dans un fichier trié par nom
 */
#include <stdio.h>
#include <string.h>

typedef struct {
    char  matricule[20];
    char  nom[20];
    char  prenom[20];
    float moyenne;
} Etudiant;

/* ---------- Partie 1 : fichier texte ---------- */

int saisir_etudiant(Etudiant *e) {
    printf("matricule nom prenom moyenne : ");
    return scanf("%19s %19s %19s %f", e->matricule, e->nom, e->prenom, &e->moyenne) == 4;
}

/* Écrit les étudiants saisis dans le fichier (mode "w" crée / "a" ajoute). */
int ecrire_etudiants(const char *fichier, const char *mode, int n) {
    FILE *f = fopen(fichier, mode);
    if (f == NULL) { perror("fopen"); return -1; }

    for (int i = 0; i < n; i++) {
        Etudiant e;
        if (!saisir_etudiant(&e)) break;
        fprintf(f, "%s %s %s %.2f\n", e.matricule, e.nom, e.prenom, e.moyenne);
    }
    fclose(f);
    return 0;
}

/* Affiche le contenu du fichier et retourne la moyenne générale. */
float afficher_etudiants(const char *fichier) {
    FILE *f = fopen(fichier, "r");
    Etudiant e;
    float somme = 0;
    int n = 0;

    if (f == NULL) { perror("fopen"); return 0; }
    while (fscanf(f, "%19s %19s %19s %f", e.matricule, e.nom, e.prenom, &e.moyenne) == 4) {
        printf("%-10s %-12s %-12s %5.2f\n", e.matricule, e.nom, e.prenom, e.moyenne);
        somme += e.moyenne;
        n++;
    }
    fclose(f);
    return (n > 0) ? somme / n : 0;
}

/* ---------- Partie 2 : fichier binaire trié par nom ---------- */

/*
 * Insère e à sa place (ordre alphabétique des noms) dans un fichier binaire
 * déjà trié, en décalant les enregistrements suivants d'une case.
 */
int inserer_trie(const char *fichier, Etudiant e) {
    FILE *f = fopen(fichier, "rb+");
    if (f == NULL) f = fopen(fichier, "wb+");        /* le fichier n'existe pas encore */
    if (f == NULL) { perror("fopen"); return -1; }

    fseek(f, 0, SEEK_END);
    long n = ftell(f) / (long)sizeof(Etudiant);      /* nombre d'enregistrements */

    /* 1. Chercher la position d'insertion p. */
    long p = 0;
    Etudiant courant;
    while (p < n) {
        fseek(f, p * (long)sizeof(Etudiant), SEEK_SET);
        fread(&courant, sizeof(Etudiant), 1, f);
        if (strcmp(courant.nom, e.nom) > 0) break;
        p++;
    }

    /* 2. Décaler les enregistrements p..n-1 vers la droite (en partant de la fin). */
    for (long i = n - 1; i >= p; i--) {
        fseek(f, i * (long)sizeof(Etudiant), SEEK_SET);
        fread(&courant, sizeof(Etudiant), 1, f);
        fseek(f, (i + 1) * (long)sizeof(Etudiant), SEEK_SET);
        fwrite(&courant, sizeof(Etudiant), 1, f);
    }

    /* 3. Écrire le nouvel enregistrement. */
    fseek(f, p * (long)sizeof(Etudiant), SEEK_SET);
    fwrite(&e, sizeof(Etudiant), 1, f);

    fclose(f);
    return 0;
}

void afficher_binaire(const char *fichier) {
    FILE *f = fopen(fichier, "rb");
    Etudiant e;
    if (f == NULL) { perror("fopen"); return; }
    while (fread(&e, sizeof(Etudiant), 1, f) == 1)
        printf("%-12s %-12s %5.2f\n", e.nom, e.prenom, e.moyenne);
    fclose(f);
}

int main(void) {
    int n;

    printf("--- Partie 1 : fichier texte ---\nNombre d'etudiants : ");
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    if (ecrire_etudiants("etudiants.txt", "w", n) != 0) return 1;
    printf("Moyenne generale : %.2f\n\n", afficher_etudiants("etudiants.txt"));

    printf("Ajout d'un etudiant :\n");
    ecrire_etudiants("etudiants.txt", "a", 1);
    printf("Moyenne generale : %.2f\n\n", afficher_etudiants("etudiants.txt"));

    printf("--- Partie 2 : insertion triee dans un fichier binaire ---\n");
    remove("etudiants.bin");
    for (int i = 0; i < 3; i++) {
        Etudiant e;
        if (!saisir_etudiant(&e)) break;
        inserer_trie("etudiants.bin", e);
    }
    afficher_binaire("etudiants.bin");
    return 0;
}
