#ifndef DECODE_MATRIX_H
#define DECODE_MATRIX_H

// Inclure les bibliothèques nécessaires
#include <stdio.h>
#include <stdlib.h>

#define TAILLE 5

// Structure pour une liste dynamique
typedef struct {
    int *data;
    int size;
    int capacity;
} List;

// Fonction pour initialiser une liste dynamique
List* create_list(int capacity);

// Fonction pour ajouter un élément à une liste dynamique
void add_to_list(List *list, int value);

// Fonction pour vérifier si une liste contient un élément
int contains(List *list, int value);

// Fonction pour libérer la mémoire d'une liste dynamique
void free_list(List *list);

// Fonction qui implémente l'algorithme
List** process_matrix(int matrix[TAILLE][TAILLE]);

// Fonction pour imprimer les listes
void print_lists(List **lists);

#endif // DECODE_MATRIX_H
