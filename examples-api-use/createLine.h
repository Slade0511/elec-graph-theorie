#ifndef CREATELINE_H
#define CREATELINE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Dimensions de la matrice
#define DIM 32

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

// Fonction pour initialiser une matrice 32x32 avec des zéros
void init_matrix(int matrix[DIM][DIM]);

// Fonction pour placer un point sur la matrice
void place_point(int matrix[DIM][DIM], Point p);

// Fonction pour afficher la matrice 32x32
void print_matrix(int matrix[DIM][DIM]);

// Fonction pour trouver l'index d'un numéro dans une liste
int find_index(int* list, int size, int number);

// Fonction pour convertir les paires de numéros en paires de points
Point** convert_pairs_to_points(int** pairs, int num_pairs, PointList* point_list, int listNumero[][DIM], int* num_points_pairs);

// Fonction pour libérer la mémoire des paires de points
void free_points_pairs(Point** points_pairs, int num_points_pairs);

// Fonction pour afficher les paires de points
void print_points_pairs(Point** points_pairs, int num_points_pairs);

// Fonction pour libérer la mémoire des paires
void free_pairs(int** pairs, int num_pairs);

// Fonction pour afficher les paires
void print_pairs(int** pairs, int num_pairs);

// Fonction pour trouver les paires de numéros qui se croisent sans doublons
int** find_crossing_pairs(int matrix[][DIM], int taille, int* num_pairs);

// Fonction pour afficher une liste de points
void print_point_list(PointList *point_list, int taille);

// Fonction pour libérer la mémoire d'une liste de points
void free_point_list(PointList *point_list, int taille);

// Fonction pour créer une liste de points à partir d'une liste d'entiers
PointList* process_list(int liste[][DIM], int taille);

// Fonction pour arrondir un nombre à l'entier inférieur
int arrondit_inferieur(float nombre);

// Fonction pour initialiser une liste de points
PointList create_point_list(int taille);

// Fonction pour créer un point
Point create_point(int longueur, int hauteur);

void place_and_connect_points(Point** points_pairs, int num_points_pairs, int matrix[DIM][DIM]);


#endif // CREATELINE_H
