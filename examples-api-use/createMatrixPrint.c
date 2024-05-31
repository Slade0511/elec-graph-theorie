#include <stdio.h>
#include <stdlib.h>

#define DIM 32

// Structure pour représenter un point
typedef struct {
    int x;
    int y;
} Point;

// Fonction pour initialiser une matrice 32x32 avec des zéros
void init_matrix(int matrix[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Fonction pour placer un point sur la matrice
void place_point(int matrix[DIM][DIM], Point p) {
    int x = p.x;
    int y = p.y;

    // Convertir les coordonnées en partant du bas à gauche
    int matrix_y = DIM - y - 1;

    if (x >= 0 && x < DIM && y >= 0 && y < DIM) {
        matrix[matrix_y][x] = 1;
    } else {
        printf("Point (%d, %d) is out of bounds.\n", x, y);
    }
}

// Fonction pour afficher la matrice 32x32
void print_matrix(int matrix[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/*int main() {
    // Initialisation de la matrice 32x32
    int matrix[DIM][DIM];
    init_matrix(matrix);

    // Exemple de points à placer
    Point points[] = {
        {16, 27},
        {8, 15},
        {5, 5},
        {31, 0},
        {0, 31}
    };

    int num_points = sizeof(points) / sizeof(points[0]);

    // Placement des points sur la matrice
    for (int i = 0; i < num_points; i++) {
        place_point(matrix, points[i]);
    }

    // Affichage de la matrice 32x32
    print_matrix(matrix);

    return 0;
}*/
