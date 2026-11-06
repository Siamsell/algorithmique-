/*
 * liste_chainee.cpp : liste simplement chaînée d'entiers.
 * Opérations : insertion (début / fin), affichage, concaténation,
 * partition en deux moitiés, tri, inversion, suppression, libération.
 */
#include <iostream>
using namespace std;

struct Element {
    int       info;
    Element  *suivant;
};

/* Insertion en tête : O(1). */
void inserer_debut(Element *&debut, int x) {
    Element *nv = new Element{x, debut};
    debut = nv;
}

/* Insertion en queue : O(n) (parcours jusqu'au dernier élément). */
void inserer_fin(Element *&debut, int x) {
    Element *nv = new Element{x, nullptr};
    if (debut == nullptr) { debut = nv; return; }
    Element *courant = debut;
    while (courant->suivant != nullptr) courant = courant->suivant;
    courant->suivant = nv;
}

void afficher(const Element *courant) {
    if (courant == nullptr) { cout << "(liste vide)" << endl; return; }
    for (; courant != nullptr; courant = courant->suivant)
        cout << "[" << courant->info << "]";
    cout << endl;
}

/* Libère toute la mémoire de la liste. */
void liberer(Element *&debut) {
    while (debut != nullptr) {
        Element *sup = debut;
        debut = debut->suivant;
        delete sup;
    }
}

/* d3 = copie de d1 suivie d'une copie de d2 (d1 et d2 ne sont pas modifiées). */
void concatener(const Element *d1, const Element *d2, Element *&d3) {
    for (const Element *c = d1; c != nullptr; c = c->suivant) inserer_fin(d3, c->info);
    for (const Element *c = d2; c != nullptr; c = c->suivant) inserer_fin(d3, c->info);
}

/* Copie les n/2 premiers éléments de d1 dans d2 et le reste dans d3. */
void partitionner(const Element *d1, Element *&d2, Element *&d3, int n) {
    const Element *courant = d1;
    for (int i = 0; i < n / 2 && courant != nullptr; i++, courant = courant->suivant)
        inserer_fin(d2, courant->info);
    for (; courant != nullptr; courant = courant->suivant)
        inserer_fin(d3, courant->info);
}

/* Tri par échange des valeurs (tri par sélection), O(n^2). */
void trier(Element *d) {
    for (Element *i = d; i != nullptr; i = i->suivant)
        for (Element *j = i->suivant; j != nullptr; j = j->suivant)
            if (j->info < i->info) {
                int tmp = i->info;
                i->info = j->info;
                j->info = tmp;
            }
}

/* Inverse la liste en place en retournant les liens, O(n). */
Element *inverser(Element *tete) {
    Element *precedent = nullptr;
    while (tete != nullptr) {
        Element *suivant = tete->suivant;
        tete->suivant = precedent;
        precedent = tete;
        tete = suivant;
    }
    return precedent;   // nouvelle tête
}

/* Supprime la première occurrence de val. Retourne true si trouvée. */
bool supprimer_valeur(Element *&debut, int val) {
    Element *precedent = nullptr, *courant = debut;
    while (courant != nullptr && courant->info != val) {
        precedent = courant;
        courant = courant->suivant;
    }
    if (courant == nullptr) return false;

    if (precedent == nullptr) debut = courant->suivant;
    else                      precedent->suivant = courant->suivant;
    delete courant;
    return true;
}

int main() {
    Element *l1 = nullptr, *l2 = nullptr, *l3 = nullptr;
    Element *moitie1 = nullptr, *moitie2 = nullptr;

    for (int x : {5, 2, 9}) inserer_fin(l1, x);
    for (int x : {7, 1})    inserer_fin(l2, x);
    inserer_debut(l1, 100);

    cout << "l1 : ";  afficher(l1);
    cout << "l2 : ";  afficher(l2);

    concatener(l1, l2, l3);
    cout << "l1 + l2 : ";  afficher(l3);

    trier(l3);
    cout << "trie : ";  afficher(l3);

    partitionner(l3, moitie1, moitie2, 6);
    cout << "moitie 1 : ";  afficher(moitie1);
    cout << "moitie 2 : ";  afficher(moitie2);

    l3 = inverser(l3);
    cout << "inverse : ";  afficher(l3);

    cout << "suppression de 9 : " << (supprimer_valeur(l3, 9) ? "ok" : "absent") << endl;
    cout << "suppression de 42 : " << (supprimer_valeur(l3, 42) ? "ok" : "absent") << endl;
    afficher(l3);

    liberer(l1); liberer(l2); liberer(l3);
    liberer(moitie1); liberer(moitie2);
    return 0;
}
