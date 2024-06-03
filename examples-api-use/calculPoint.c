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
Point create_point(int longueur, int hauteur) {
    Point point;
    point.longueur = longueur;
    point.hauteur = hauteur;
    return point;
}

// Fonction pour initialiser une liste de points
PointList create_point_list(int taille) {
    PointList list;
    list.points = (Point*)malloc(taille * sizeof(Point));
    list.taille = taille;
    return list;
}

// Fonction pour arrondir un nombre à l'entier inférieur
int arrondit_inferieur(float nombre) {
    return (int)floor(nombre);
}

// Fonction pour créer une liste de points à partir d'une liste d'entiers
PointList* process_list(List** liste, int tailleH) {
    PointList* point_list = (PointList*)malloc(tailleH * sizeof(PointList));

    int block_height = 32 / tailleH;

    for (int i = 0; i < tailleH; i++) {
        int elements = liste[i]->size;
        point_list[i] = create_point_list(elements);
        int block_width = 32 / elements;

        for (int j = 0; j < elements; j++) {
            int longueur = block_width * j + block_width / 2;
            int hauteur = 32 - (block_height * i + block_height / 2);
            point_list[i].points[j] = create_point(longueur, hauteur);
        }
    }

    return point_list;
}

// Fonction pour libérer la mémoire d'une liste de points
void free_point_list(PointList *point_list, int taille) {
    for (int i = 0; i < taille; i++) {
        free(point_list[i].points);
    }
    free(point_list);
}

// Fonction pour afficher une liste de points
void print_point_list(PointList *point_list, int taille) {
    for (int i = 0; i < taille; i++) {
        printf("List %d:\n", i);
        for (int j = 0; j < point_list[i].taille; j++) {
            printf("Point %d: Longueur = %d, Hauteur = %d\n", j, point_list[i].points[j].longueur, point_list[i].points[j].hauteur);
        }
        printf("\n");
    }
}

/*int main() {
    // Exemple de liste d'entiers
    int liste_entiers[3][2] = {{1, 0}, {2, 3}, {2, 5}};

    // Création de la liste de points
    PointList *point_list = process_list(liste_entiers, 3);

    // Affichage de la liste de points
    print_point_list(point_list, 3);

    // Libération de la mémoire
    free_point_list(point_list, 3);

    return 0;
}*/
