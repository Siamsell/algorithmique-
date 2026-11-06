/*
 * liste_processus.cpp : tableau dynamique de M listes chaînées de processus.
 * Chaque processus a un identifiant et une priorité.
 * Opérations : construction, affichage, inversion, suppression de la première
 * occurrence d'une priorité donnée dans chaque liste, libération mémoire.
 */
#include <iostream>
#include <cstdlib>
using namespace std;

struct Processus {
    int        id;
    int        priorite;
    Processus *suivant;
};

/* Construit une liste de n processus (id = 1..n, priorité aléatoire 0..9). */
Processus *construire_liste(int n) {
    Processus *tete = nullptr, *queue = nullptr;
    for (int i = 1; i <= n; i++) {
        Processus *p = new Processus{i, rand() % 10, nullptr};
        if (tete == nullptr) tete = p;
        else                 queue->suivant = p;
        queue = p;
    }
    return tete;
}

void afficher_liste(const Processus *p) {
    for (; p != nullptr; p = p->suivant)
        cout << "(" << p->id << ", prio " << p->priorite << ") ";
    cout << endl;
}

Processus *inverser_liste(Processus *tete) {
    Processus *precedent = nullptr;
    while (tete != nullptr) {
        Processus *suivant = tete->suivant;
        tete->suivant = precedent;
        precedent = tete;
        tete = suivant;
    }
    return precedent;
}

/* Supprime le premier processus de priorité val ; retourne la (nouvelle) tête. */
Processus *supprimer_priorite(Processus *tete, int val) {
    Processus *precedent = nullptr, *courant = tete;
    while (courant != nullptr && courant->priorite != val) {
        precedent = courant;
        courant = courant->suivant;
    }
    if (courant == nullptr) return tete;                 // priorité absente

    if (precedent == nullptr) tete = courant->suivant;   // suppression en tête
    else                      precedent->suivant = courant->suivant;
    delete courant;
    return tete;
}

void liberer_liste(Processus *tete) {
    while (tete != nullptr) {
        Processus *suivant = tete->suivant;
        delete tete;
        tete = suivant;
    }
}

void afficher_tout(Processus **tab, int m, const char *titre) {
    cout << "--- " << titre << " ---" << endl;
    for (int i = 0; i < m; i++) {
        cout << "Liste " << i << " : ";
        afficher_liste(tab[i]);
    }
}

int main() {
    const int M = 3;        // nombre de listes
    const int N = 4;        // processus par liste
    const int VAL = 5;      // priorité à supprimer

    srand(42);              // graine fixe : résultats reproductibles

    Processus **tab = new Processus*[M];
    for (int i = 0; i < M; i++) tab[i] = construire_liste(N);
    afficher_tout(tab, M, "Listes initiales");

    for (int i = 0; i < M; i++) tab[i] = inverser_liste(tab[i]);
    afficher_tout(tab, M, "Apres inversion");

    for (int i = 0; i < M; i++) tab[i] = supprimer_priorite(tab[i], VAL);
    cout << "(suppression de la premiere priorite " << VAL << " dans chaque liste)" << endl;
    afficher_tout(tab, M, "Apres suppression");

    for (int i = 0; i < M; i++) liberer_liste(tab[i]);
    delete[] tab;
    return 0;
}
