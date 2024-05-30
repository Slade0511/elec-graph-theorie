#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAILLE 5
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
PointList* process_list(int liste[][TAILLE], int taille) {
    PointList *point_list = (PointList*)malloc(taille * sizeof(PointList));

    int block_height = DIM / taille;

    for (int i = 0; i < taille; i++) {
        int elements = 0;
        for (int k = 0; k < TAILLE; k++) {
            if (liste[i][k] != 0) elements++;
        }
        point_list[i] = create_point_list(elements);
        int block_width = DIM / elements;

        for (int j = 0; j < elements; j++) {
            int longueur = block_width * j + block_width / 2;
            int hauteur = block_height * i + block_height / 2;
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

// Fonction pour initialiser une matrice 32x32
void init_matrix(int matrix[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Fonction pour tracer une ligne entre deux points
void draw_line(int matrix[DIM][DIM], Point p1, Point p2) {
    int x1 = p1.longueur;
    int y1 = p1.hauteur;
    int x2 = p2.longueur;
    int y2 = p2.hauteur;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        matrix[y1][x1] = 1;

        if (x1 == x2 && y1 == y2) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Fonction pour traiter la matrice et générer la matrice 32x32 avec les connexions
void process_and_draw(int matrix[TAILLE][TAILLE], PointList *point_list, int result[DIM][DIM], int listNumero[3][TAILLE]) {
    init_matrix(result);

    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (matrix[i][j] == 1) {
                Point p1, p2;
                int found_p1 = 0, found_p2 = 0;
                for (int k = 0; k < TAILLE && !(found_p1 && found_p2); k++) {
                    if (listNumero[i][k] == i + 1) {
                        p1 = point_list[i].points[k];
                        found_p1 = 1;
                    }
                    if (listNumero[j][k] == j + 1) {
                        p2 = point_list[j].points[k];
                        found_p2 = 1;
                    }
                }
                if (found_p1 && found_p2) {
                    draw_line(result, p1, p2);
                }
            }
        }
    }

    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < point_list[i].taille; j++) {
            Point p = point_list[i].points[j];
            result[p.hauteur][p.longueur] = 1;
        }
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

int main() {
    // Matrice d'origine
    int matrix[TAILLE][TAILLE] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0}
    };

    // Exemple de liste d'entiers
    int liste_entiers[3][TAILLE] = {{1, 0, 0, 0, 0}, {2, 3, 0, 0, 0}, {4, 5, 0, 0, 0}};

    // Création de la liste de points
    PointList *point_list = process_list(liste_entiers, 3);

    // Affichage de la liste de points
    print_point_list(point_list, 3);

    // Initialisation de la matrice 32x32
    static int result[DIM][DIM];
    process_and_draw(matrix, point_list, result, liste_entiers);

    // Affichage de la matrice 32x32
    print_matrix(result);

    // Libération de la mémoire
    free_point_list(point_list, 3);

    return 0;
}
