#ifndef CALCULPOINT_H
#define CALCULPOINT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "decode_matrix.h"


// Structure pour représenter un point
typedef struct {
    int longueur;
    int hauteur;
} Point;

// Structure pour représenter une liste de points
typedef struct {
    Point *points;
    int taille;
} PointList;

// Fonction pour créer un point
Point create_point(int longueur, int hauteur);

// Fonction pour initialiser une liste de points
PointList create_point_list(int taille);

// Fonction pour arrondir un nombre à l'entier inférieur
int arrondit_inferieur(float nombre);

// Fonction pour créer une liste de points à partir d'une liste d'entiers
PointList* process_list(List** liste, int taille);

// Fonction pour libérer la mémoire d'une liste de points
void free_point_list(PointList *point_list, int taille);

int find_index(const std::vector<int>& list, int number);


// Fonction pour afficher une liste de points
void print_point_list(PointList *point_list, int taille);

#endif // CALCULPOINT_H
