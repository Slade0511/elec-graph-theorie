#ifndef CREATELINE_H
#define CREATELINE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculPoint.h"

// Dimensions de la matrice
#define DIM 32
#define TAILLE 5

// Structure pour représenter un point

// Structure pour représenter une liste de points

// Fonction pour initialiser une matrice 32x32 avec des zéros
void init_matrix(int matrix[DIM][DIM]);

// Fonction pour placer un point sur la matrice
void place_point(int matrix[DIM][DIM], Point p);

// Fonction pour afficher la matrice 32x32
void print_matrix(int matrix[DIM][DIM]);

// Fonction pour trouver l'index d'un numéro dans une liste
int find_index(int* list, int size, int number);

// Fonction pour convertir les paires de numéros en paires de points
Point** convert_pairs_to_points(int** pairs, int num_pairs, PointList* point_list, List** listNumero, int* num_points_pairs);

// Fonction pour libérer la mémoire des paires de points
void free_points_pairs(Point** points_pairs, int num_points_pairs);

// Fonction pour afficher les paires de points
void print_points_pairs(Point** points_pairs, int num_points_pairs);

// Fonction pour libérer la mémoire des paires
void free_pairs(int** pairs, int num_pairs);

// Fonction pour afficher les paires
void print_pairs(int** pairs, int num_pairs);

// Fonction pour trouver les paires de numéros qui se croisent sans doublons
int** find_crossing_pairs(int matrix[TAILLE][TAILLE], int taille, int* num_pairs);


void place_and_connect_points(Point** points_pairs, int num_points_pairs, int matrix[DIM][DIM]);


#endif // CREATELINE_H
