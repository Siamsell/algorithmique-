/*
 * concatenation_listes.cpp : deux façons de concaténer des listes chaînées.
 *
 *  - SANS sacrifice : on construit une nouvelle liste c (copie de a puis de b).
 *                     a et b restent intactes.            Coût : O(|a| + |b|) mémoire en plus.
 *  - AVEC sacrifice : on relie le dernier nœud de a au premier de b.
 *                     a et b sont "consommées".           Pas de copie.
 */
#include <iostream>
using namespace std;

struct Noeud {
    int     valeur;
    Noeud  *suivant;
};

void afficher(const Noeud *n) {
    for (; n != nullptr; n = n->suivant) cout << n->valeur << " ";
    cout << endl;
}

void liberer(Noeud *&tete) {
    while (tete != nullptr) {
        Noeud *sup = tete;
        tete = tete->suivant;
        delete sup;
    }
}

/* Ajoute à la fin de la liste en O(1) grâce à un pointeur sur le dernier nœud. */
void ajouter_fin(Noeud *&tete, Noeud *&queue, int valeur) {
    Noeud *nv = new Noeud{valeur, nullptr};
    if (tete == nullptr) tete = nv;
    else                 queue->suivant = nv;
    queue = nv;
}

Noeud *concatener_sans_sacrifice(const Noeud *a, const Noeud *b) {
    Noeud *c = nullptr, *queue = nullptr;
    for (; a != nullptr; a = a->suivant) ajouter_fin(c, queue, a->valeur);
    for (; b != nullptr; b = b->suivant) ajouter_fin(c, queue, b->valeur);
    return c;
}

Noeud *concatener_avec_sacrifice(Noeud *&a, Noeud *&b) {
    Noeud *c;
    if (a == nullptr) {
        c = b;
    } else {
        Noeud *dernier = a;
        while (dernier->suivant != nullptr) dernier = dernier->suivant;
        dernier->suivant = b;
        c = a;
    }
    a = b = nullptr;       // a et b ne possèdent plus rien : c est le seul propriétaire
    return c;
}

Noeud *creer(initializer_list<int> valeurs) {
    Noeud *tete = nullptr, *queue = nullptr;
    for (int v : valeurs) ajouter_fin(tete, queue, v);
    return tete;
}

int main() {
    Noeud *a = creer({1, 2, 3});
    Noeud *b = creer({7, 8, 9});

    Noeud *c1 = concatener_sans_sacrifice(a, b);
    cout << "Sans sacrifice :" << endl;
    cout << "  c = ";  afficher(c1);
    cout << "  a = ";  afficher(a);
    cout << "  b = ";  afficher(b);

    liberer(c1); liberer(a); liberer(b);

    a = creer({4, 5, 6});
    b = creer({10, 11, 12});

    Noeud *c2 = concatener_avec_sacrifice(a, b);
    cout << "Avec sacrifice :" << endl;
    cout << "  c = ";  afficher(c2);
    cout << "  a = ";  afficher(a);
    cout << "  b = ";  afficher(b);

    liberer(c2);
    return 0;
}
