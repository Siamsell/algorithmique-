/*
 * Gestion d'étudiants - application console en C
 *
 * Fonctionnalités : ajouter, afficher, rechercher, modifier, supprimer,
 * calculer la moyenne pondérée. Chaque étudiant est sauvegardé dans un
 * fichier texte du dossier "database/".
 *
 * Compilation : gcc -Wall -Wextra -o gestion_etudiants main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#ifdef _WIN32
  #include <direct.h>
  #define CREER_DOSSIER(d) _mkdir(d)
#else
  #include <sys/stat.h>
  #include <sys/types.h>
  #define CREER_DOSSIER(d) mkdir(d, 0755)
#endif

#define DATABASE_DIR   "database"
#define MAX_ETUDIANTS  100
#define NB_MODULES     5

/* ---------- Structures ---------- */

struct Module {
    char  nom_module[50];
    float coefficient;
    float note;
};

struct Etudiant {
    int    id;
    char   nom[50];
    char   prenom[50];
    char   adresse[100];
    char   email[100];
    int    age;
    float  moyenne;
    struct Module module[NB_MODULES];
};

/* ---------- Saisie sécurisée ---------- */

/* Lit une ligne sans débordement et supprime le '\n' final. */
static void lire_ligne(const char *message, char *dest, size_t taille) {
    printf("%s", message);
    if (fgets(dest, (int)taille, stdin) == NULL) { dest[0] = '\0'; return; }
    dest[strcspn(dest, "\n")] = '\0';
}

static int lire_entier(const char *message) {
    char buf[64];
    int valeur;
    for (;;) {
        lire_ligne(message, buf, sizeof buf);
        if (sscanf(buf, "%d", &valeur) == 1) return valeur;
        printf("Entier invalide.\n");
    }
}

static float lire_reel(const char *message) {
    char buf[64];
    float valeur;
    for (;;) {
        lire_ligne(message, buf, sizeof buf);
        if (sscanf(buf, "%f", &valeur) == 1) return valeur;
        printf("Nombre invalide.\n");
    }
}

/* ---------- Validation ---------- */

/* Vrai si la chaîne est non vide et ne contient que des lettres. */
static bool est_alphabetique(const char *chaine) {
    if (chaine[0] == '\0') return false;
    for (size_t i = 0; chaine[i] != '\0'; i++)
        if (!isalpha((unsigned char)chaine[i])) return false;
    return true;
}

/* Vrai si l'email contient un seul '@' suivi, plus loin, d'un '.'. */
static bool est_email_valide(const char *email) {
    int arobases = 0;
    for (size_t i = 0; email[i] != '\0'; i++)
        if (email[i] == '@') arobases++;
    if (arobases != 1) return false;

    const char *arobase = strchr(email, '@');
    if (arobase == email) return false;                 /* rien avant le '@' */
    const char *point = strchr(arobase, '.');
    return point != NULL && point > arobase + 1 && point[1] != '\0';
}

static void lire_mot_alphabetique(const char *message, char *dest, size_t taille) {
    lire_ligne(message, dest, taille);
    while (!est_alphabetique(dest))
        lire_ligne("  Valeur invalide (lettres uniquement), recommencez : ", dest, taille);
}

static void lire_email(const char *message, char *dest, size_t taille) {
    lire_ligne(message, dest, taille);
    while (!est_email_valide(dest))
        lire_ligne("  Email invalide, recommencez : ", dest, taille);
}

/* ---------- Persistance (un fichier texte par étudiant) ---------- */

static void chemin_fichier(char *dest, size_t taille, int id) {
    snprintf(dest, taille, "%s/etudiant_%d.txt", DATABASE_DIR, id);
}

static void sauvegarder_etudiant(const struct Etudiant *e) {
    char chemin[128];
    chemin_fichier(chemin, sizeof chemin, e->id);

    FILE *f = fopen(chemin, "w");
    if (f == NULL) {
        printf("Erreur : impossible d'ecrire %s\n", chemin);
        return;
    }
    fprintf(f, "ID: %d\n", e->id);
    fprintf(f, "Nom: %s\n", e->nom);
    fprintf(f, "Prenom: %s\n", e->prenom);
    fprintf(f, "Adresse: %s\n", e->adresse);
    fprintf(f, "Email: %s\n", e->email);
    fprintf(f, "Age: %d\n", e->age);
    fprintf(f, "Moyenne: %.2f\n", e->moyenne);
    for (int i = 0; i < NB_MODULES; i++)
        fprintf(f, "Module %d: %s (coef %.1f) note %.2f\n", i + 1,
                e->module[i].nom_module, e->module[i].coefficient, e->module[i].note);
    fclose(f);
}

/* ---------- Opérations ---------- */

/* Retourne l'indice de l'étudiant d'identifiant id, ou -1. */
static int trouver_indice(const struct Etudiant *etudiants, int nb, int id) {
    for (int i = 0; i < nb; i++)
        if (etudiants[i].id == id) return i;
    return -1;
}

static void afficher_etudiant(const struct Etudiant *e) {
    printf("ID: %d\n", e->id);
    printf("Nom: %s\n", e->nom);
    printf("Prenom: %s\n", e->prenom);
    printf("Adresse: %s\n", e->adresse);
    printf("Email: %s\n", e->email);
    printf("Age: %d\n", e->age);
    printf("Moyenne: %.2f\n", e->moyenne);
}

/* Moyenne pondérée : somme(coef * note) / somme(coef). */
static float calculer_moyenne_etudiant(const struct Etudiant *e) {
    float somme_coef = 0, somme_notes = 0;
    for (int i = 0; i < NB_MODULES; i++) {
        somme_coef  += e->module[i].coefficient;
        somme_notes += e->module[i].coefficient * e->module[i].note;
    }
    return (somme_coef > 0) ? somme_notes / somme_coef : 0;
}

static void saisir_identite(struct Etudiant *e) {
    lire_mot_alphabetique("Nom : ", e->nom, sizeof e->nom);
    lire_mot_alphabetique("Prenom : ", e->prenom, sizeof e->prenom);
    lire_ligne("Adresse : ", e->adresse, sizeof e->adresse);
    lire_email("Email : ", e->email, sizeof e->email);
    e->age = lire_entier("Age : ");
}

static void ajouter(struct Etudiant *etudiants, int *nb) {
    if (*nb >= MAX_ETUDIANTS) {
        printf("Capacite maximale atteinte (%d etudiants).\n", MAX_ETUDIANTS);
        return;
    }

    struct Etudiant e;
    printf("--- Ajout d'un etudiant ---\n");

    e.id = lire_entier("ID : ");
    if (trouver_indice(etudiants, *nb, e.id) != -1) {
        printf("Cet ID existe deja.\n");
        return;
    }

    saisir_identite(&e);

    printf("Notes des %d modules :\n", NB_MODULES);
    for (int i = 0; i < NB_MODULES; i++) {
        printf("Module %d\n", i + 1);
        lire_ligne("  Nom du module : ", e.module[i].nom_module, sizeof e.module[i].nom_module);
        e.module[i].coefficient = lire_reel("  Coefficient : ");
        e.module[i].note        = lire_reel("  Note : ");
    }
    e.moyenne = calculer_moyenne_etudiant(&e);

    etudiants[(*nb)++] = e;
    sauvegarder_etudiant(&e);
    printf("Etudiant ajoute avec succes.\n");
}

static void afficher(const struct Etudiant *etudiants, int nb) {
    if (nb == 0) { printf("Aucun etudiant enregistre.\n"); return; }
    printf("--- Liste des etudiants ---\n");
    for (int i = 0; i < nb; i++) {
        afficher_etudiant(&etudiants[i]);
        printf("\n");
    }
}

static void rechercher(const struct Etudiant *etudiants, int nb) {
    if (nb == 0) { printf("Aucun etudiant enregistre.\n"); return; }
    int i = trouver_indice(etudiants, nb, lire_entier("ID a rechercher : "));
    if (i == -1) printf("Aucun etudiant avec cet ID.\n");
    else         afficher_etudiant(&etudiants[i]);
}

static void modifier(struct Etudiant *etudiants, int nb) {
    if (nb == 0) { printf("Aucun etudiant enregistre.\n"); return; }
    int i = trouver_indice(etudiants, nb, lire_entier("ID a modifier : "));
    if (i == -1) { printf("Aucun etudiant avec cet ID.\n"); return; }

    printf("--- Modification (saisir les nouvelles valeurs) ---\n");
    saisir_identite(&etudiants[i]);
    sauvegarder_etudiant(&etudiants[i]);
    printf("Informations modifiees avec succes.\n");
}

static void supprimer(struct Etudiant *etudiants, int *nb) {
    if (*nb == 0) { printf("Aucun etudiant enregistre.\n"); return; }
    int id = lire_entier("ID a supprimer : ");
    int i = trouver_indice(etudiants, *nb, id);
    if (i == -1) { printf("Aucun etudiant avec cet ID.\n"); return; }

    for (int j = i; j < *nb - 1; j++)           /* décalage vers la gauche */
        etudiants[j] = etudiants[j + 1];
    (*nb)--;

    char chemin[128];
    chemin_fichier(chemin, sizeof chemin, id);
    remove(chemin);
    printf("Etudiant supprime avec succes.\n");
}

static void afficher_moyennes(const struct Etudiant *etudiants, int nb) {
    if (nb == 0) { printf("Aucun etudiant enregistre.\n"); return; }
    printf("--- Moyennes ---\n");
    float total = 0;
    for (int i = 0; i < nb; i++) {
        printf("%d  %s %s : %.2f\n", etudiants[i].id, etudiants[i].nom,
               etudiants[i].prenom, etudiants[i].moyenne);
        total += etudiants[i].moyenne;
    }
    printf("Moyenne generale de la promotion : %.2f\n", total / nb);
}

/* ---------- Programme principal ---------- */

int main(void) {
    CREER_DOSSIER(DATABASE_DIR);   /* sans effet si le dossier existe déjà */

    struct Etudiant etudiants[MAX_ETUDIANTS];
    int nb = 0, choix;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher les etudiants\n");
        printf("3. Rechercher un etudiant par ID\n");
        printf("4. Modifier un etudiant\n");
        printf("5. Supprimer un etudiant\n");
        printf("6. Afficher les moyennes\n");
        printf("7. Quitter\n");
        choix = lire_entier("Votre choix : ");

        switch (choix) {
            case 1: ajouter(etudiants, &nb);          break;
            case 2: afficher(etudiants, nb);          break;
            case 3: rechercher(etudiants, nb);        break;
            case 4: modifier(etudiants, nb);          break;
            case 5: supprimer(etudiants, &nb);        break;
            case 6: afficher_moyennes(etudiants, nb); break;
            case 7: printf("Au revoir !\n");          break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 7);

    return 0;
}
