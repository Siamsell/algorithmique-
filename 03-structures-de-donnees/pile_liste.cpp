/*
 * pile_liste.cpp : pile (LIFO) implémentée avec une liste chaînée.
 *   empiler  == insertion en tête
 *   depiler  == suppression en tête
 * Application : partitionner une pile en deux piles de n/2 éléments
 * en conservant l'ordre, à l'aide d'une pile auxiliaire.
 */
#include <iostream>
using namespace std;

struct Pile {
    int   info;
    Pile *suivant;
};

void empiler(Pile *&sommet, int x) {
    sommet = new Pile{x, sommet};
}

/* Retourne false si la pile est vide, sinon écrit la valeur dans x. */
bool depiler(Pile *&sommet, int &x) {
    if (sommet == nullptr) return false;
    Pile *sup = sommet;
    x = sommet->info;
    sommet = sommet->suivant;
    delete sup;
    return true;
}

void afficher(const Pile *p) {
    if (p == nullptr) { cout << "(pile vide)"; return; }
    for (; p != nullptr; p = p->suivant) cout << "[" << p->info << "]\t";
}

void liberer(Pile *&sommet) {
    int x;
    while (depiler(sommet, x)) {}
}

/*
 * Déplace les n/2 éléments du haut de `source` dans `destination`
 * (l'ordre est conservé grâce à une pile temporaire).
 */
void partitionner(Pile *&source, Pile *&destination, int n) {
    Pile *temp = nullptr;
    int val;
    for (int i = 0; i < n / 2; i++) { depiler(source, val);  empiler(temp, val); }
    for (int i = 0; i < n / 2; i++) { depiler(temp, val);    empiler(destination, val); }
}

int main() {
    Pile *p1 = nullptr, *p2 = nullptr;
    int n;

    do {
        cout << "Nombre d'elements a empiler (pair) : ";
        if (!(cin >> n)) return 1;
    } while (n <= 0 || n % 2 != 0);

    for (int i = 1; i <= n; i++) empiler(p1, i * 10);

    cout << "Pile saisie     : ";  afficher(p1);  cout << endl;

    partitionner(p1, p2, n);
    cout << "Moitie haute    : ";  afficher(p2);  cout << endl;
    cout << "Moitie basse    : ";  afficher(p1);  cout << endl;

    liberer(p1);
    liberer(p2);
    return 0;
}
