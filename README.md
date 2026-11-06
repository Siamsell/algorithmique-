# Algorithmique et structures de données en C / C++

Collection de programmes écrits pendant ma formation en algorithmique et programmation.
Chaque fichier est **autonome**, **commenté** et **compile sans avertissement**
(`-Wall -Wextra`). Les structures de données sont testées avec AddressSanitizer
(aucune fuite mémoire, aucun accès invalide).

## Contenu

| Dossier | Fichier | Notions |
|---|---|---|
| `01-bases-c` | `fonctions.c` | fonctions, parité, divisibilité par soustractions |
| | `chaines.c` | chaînes de caractères, copie, lecture sécurisée (`fgets`) |
| | `tableaux.c` | somme, tableau binaire, **fusion de tableaux triés**, décalage circulaire récursif |
| | `matrices.c` | **produit matriciel** (tableaux 2D) |
| | `recursivite.c` | Fibonacci, inversion d'une chaîne, cas de base |
| | `structures.c` | `struct` imbriquées, tableaux de structures |
| | `fichiers.c` | fichiers texte et binaires, **insertion triée dans un fichier** |
| `02-pointeurs-memoire` | `passage_parametres.cpp` | passage par valeur / adresse / référence, échange, indice du minimum |
| | `allocation_dynamique.cpp` | `new` / `delete` / `delete[]`, tableau dynamique |
| | `struct_produit.cpp` | structure passée par valeur, adresse et référence |
| `03-structures-de-donnees` | `liste_chainee.cpp` | insertion, **tri, inversion en place**, suppression, partition |
| | `concatenation_listes.cpp` | concaténation avec / sans sacrifice |
| | `liste_processus.cpp` | tableau dynamique de listes chaînées |
| | `pile_liste.cpp` | **pile** sur liste chaînée, partition avec pile auxiliaire |
| `04-projet-gestion-etudiants` | `main.c` | application console complète (voir ci-dessous) |

## Projet : gestion d'étudiants (C)

Application en ligne de commande avec menu : ajout, affichage, recherche par ID,
modification, suppression et calcul des **moyennes pondérées** par coefficient.

- Saisie sécurisée (`fgets` + `sscanf`, pas de `gets` ni de débordement de tampon)
- Validation des noms (lettres uniquement) et des adresses e-mail
- Détection des ID en double
- Persistance : un fichier texte par étudiant dans `database/`
- Portable : Windows, Linux et macOS

## Compilation et exécution

```bash
make                                      # compile tout dans build/
./build/03-structures-de-donnees/liste_chainee
./build/04-projet-gestion-etudiants/main
make clean
```

Ou un fichier seul :

```bash
gcc -Wall -Wextra 01-bases-c/tableaux.c -o tableaux && ./tableaux
g++ -Wall -Wextra 03-structures-de-donnees/pile_liste.cpp -o pile && ./pile
```

Prérequis : `gcc` / `g++` (MinGW sous Windows).

## Compétences illustrées

Pointeurs et gestion de la mémoire dynamique · listes chaînées · piles ·
récursivité · tris et fusion · manipulation de fichiers · structuration d'un projet en fonctions ·
validation des entrées.
