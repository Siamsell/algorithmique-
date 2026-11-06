/*
 * struct_produit.cpp : une structure passée par valeur, par adresse
 * et par référence.
 */
#include <iostream>
#include <string>
using namespace std;

struct Produit {
    string code;
    int    poids;
    float  prix;
};

Produit initialiser() {
    Produit p;
    p.code  = "0";
    p.poids = 0;
    p.prix  = 0;
    return p;
}

/* Par référence : modifie directement l'objet de l'appelant. */
void saisir_reference(Produit &p) {
    cout << "code poids prix : ";
    cin >> p.code >> p.poids >> p.prix;
}

/* Par adresse : même effet, avec la syntaxe des pointeurs. */
void saisir_adresse(Produit *p) {
    cout << "code poids prix : ";
    cin >> p->code >> p->poids >> p->prix;
}

/* Par valeur : copie, suffisant pour un simple affichage. */
void afficher(Produit p) {
    cout << "  code = " << p.code << ", poids = " << p.poids
         << ", prix = " << p.prix << endl;
}

int main() {
    Produit m1 = initialiser();
    Produit m2 = initialiser();

    cout << "Produits initialises :" << endl;
    afficher(m1);
    afficher(m2);

    cout << "Saisie de m1 (par reference)" << endl;
    saisir_reference(m1);
    cout << "Saisie de m2 (par adresse)" << endl;
    saisir_adresse(&m2);

    cout << "Produits modifies :" << endl;
    afficher(m1);
    afficher(m2);
    return 0;
}
