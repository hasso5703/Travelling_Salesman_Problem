# Problème du Voyageur de Commerce (TSP)

Ce projet implémente différentes méthodes de résolution du problème du voyageur de commerce appliqué aux communes françaises, en utilisant diverses heuristiques et algorithmes d'optimisation.

## À propos du projet

Le Problème du Voyageur de Commerce (Travelling Salesman Problem - TSP) est un problème d'optimisation combinatoire classique, où l'objectif est de trouver le chemin le plus court permettant de visiter toutes les villes exactement une fois et de revenir au point de départ.

Ce projet propose plusieurs approches pour résoudre ce problème NP-difficile, avec des implémentations en C.

## Fonctionnalités

- **Chargement de données** : Possibilité de charger différents ensembles de données de communes françaises (de 10 à 777 communes)
- **Visualisation** : Affichage des résultats et des statistiques de performance
- **Algorithmes implémentés** :
  - Heuristique aléatoire par permutation
  - Heuristique aléatoire par génération de listes
  - Heuristique du plus proche voisin (PPV)
  - Heuristique d'échanges de deux sommets
  - Heuristique de (dé)croisement de deux arêtes
  - Brute Force (recherche exhaustive)
  - Algorithme du Tabou (en développement)

## Installation et utilisation

### Prérequis
- Compilateur GCC

### Compilation et exécution
```bash
gcc *.c -o prgm -O3 && ./prgm
```

### Utilisation
1. Choisir le fichier de données (nombre de communes)
2. Sélectionner l'algorithme à utiliser
3. Optionnellement, améliorer la solution avec des heuristiques supplémentaires

## Structure du projet
- `main.c` : Programme principal et interface utilisateur
- `functions.c` : Implémentation des algorithmes et heuristiques
- `functions.h` : Définitions des fonctions
- Fichiers de données : `communes_X.txt` où X représente le nombre de communes

## Auteur
- Hasan BASBUNAR
