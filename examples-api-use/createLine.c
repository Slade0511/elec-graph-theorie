#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Dimensions de la matrice
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
            int hauteur = block_height * (taille - i - 1) + block_height / 2;  // Ajustement de la hauteur pour l'origine en bas à gauche
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

// Fonction pour trouver les paires de numéros qui se croisent sans doublons
int** find_crossing_pairs(int matrix[][TAILLE], int taille, int* num_pairs) {
    int max_pairs = taille * (taille - 1) / 2;
    int** pairs = (int**)malloc(max_pairs * sizeof(int*));
    *num_pairs = 0;

    for (int i = 0; i < taille; i++) {
        for (int j = i + 1; j < taille; j++) {
            if (matrix[i][j] == 1) {
                pairs[*num_pairs] = (int*)malloc(2 * sizeof(int));
                pairs[*num_pairs][0] = i + 1;
                pairs[*num_pairs][1] = j + 1;
                (*num_pairs)++;
            }
        }
    }

    return pairs;
}

// Fonction pour afficher les paires
void print_pairs(int** pairs, int num_pairs) {
    printf("[");
    for (int i = 0; i < num_pairs; i++) {
        printf("[%d, %d]", pairs[i][0], pairs[i][1]);
        if (i < num_pairs - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Fonction pour libérer la mémoire des paires
void free_pairs(int** pairs, int num_pairs) {
    for (int i = 0; i < num_pairs; i++) {
        free(pairs[i]);
    }
    free(pairs);
}

// Fonction pour trouver l'index d'un numéro dans une liste
int find_index(int* list, int size, int number) {
    for (int i = 0; i < size; i++) {
        if (list[i] == number) {
            return i;
        }
    }
    return -1;
}

// Fonction pour convertir les paires de numéros en paires de points
Point** convert_pairs_to_points(int** pairs, int num_pairs, PointList* point_list, int listNumero[][TAILLE], int* num_points_pairs) {
    Point** points_pairs = (Point**)malloc(num_pairs * sizeof(Point*));
    *num_points_pairs = 0;

    for (int i = 0; i < num_pairs; i++) {
        int num1 = pairs[i][0];
        int num2 = pairs[i][1];
        Point p1, p2;
        int found_p1 = 0, found_p2 = 0;

        for (int j = 0; j < TAILLE && !(found_p1 && found_p2); j++) {
            int index1 = find_index(listNumero[j], TAILLE, num1);
            if (index1 != -1) {
                p1 = point_list[j].points[index1];
                found_p1 = 1;
            }

            int index2 = find_index(listNumero[j], TAILLE, num2);
            if (index2 != -1) {
                p2 = point_list[j].points[index2];
                found_p2 = 1;
            }
        }

        if (found_p1 && found_p2) {
            points_pairs[*num_points_pairs] = (Point*)malloc(2 * sizeof(Point));
            points_pairs[*num_points_pairs][0] = p1;
            points_pairs[*num_points_pairs][1] = p2;
            (*num_points_pairs)++;
        }
    }

    return points_pairs;
}

// Fonction pour afficher les paires de points
void print_points_pairs(Point** points_pairs, int num_points_pairs) {
    printf("[");
    for (int i = 0; i < num_points_pairs; i++) {
        printf("[(%d, %d), (%d, %d)]", points_pairs[i][0].longueur, points_pairs[i][0].hauteur, points_pairs[i][1].longueur, points_pairs[i][1].hauteur);
        if (i < num_points_pairs - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Fonction pour libérer la mémoire des paires de points
void free_points_pairs(Point** points_pairs, int num_points_pairs) {
    for (int i = 0; i < num_points_pairs; i++) {
        free(points_pairs[i]);
    }
    free(points_pairs);
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
    int e2;

    while (1) {
        // Placer le point dans la matrice
        matrix[y1][x1] = 1;

        // Vérifier si le point final est atteint
        if (x1 == x2 && y1 == y2) {
            break;
        }

        // Calculer les déplacements
        e2 = 2 * err;
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

// Fonction pour placer les points et tracer les lignes dans la matrice 32x32
void place_and_connect_points(Point** points_pairs, int num_points_pairs, int matrix[DIM][DIM]) {
    for (int i = 0; i < num_points_pairs; i++) {
        Point p1 = points_pairs[i][0];
        Point p2 = points_pairs[i][1];

        // Placer les points
        matrix[p1.hauteur][p1.longueur] = 1;
        matrix[p2.hauteur][p2.longueur] = 1;

        // Tracer la ligne entre les points
        draw_line(matrix, p1, p2);
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

    // Trouver les paires de numéros qui se croisent sans doublons
    int num_pairs;
    int** pairs = find_crossing_pairs(matrix, TAILLE, &num_pairs);

    // Afficher les paires de numéros
    print_pairs(pairs, num_pairs);

    // Convertir les paires de numéros en paires de points
    int num_points_pairs;
    Point** points_pairs = convert_pairs_to_points(pairs, num_pairs, point_list, liste_entiers, &num_points_pairs);

    // Afficher les paires de points
    print_points_pairs(points_pairs, num_points_pairs);

    // Initialisation de la matrice 32x32
    static int result[DIM][DIM];
    init_matrix(result);

    // Placer et relier les points dans la matrice 32x32
    place_and_connect_points(points_pairs, num_points_pairs, result);

    // Affichage de la matrice 32x32
    print_matrix(result);

    // Libération de la mémoire
    free_point_list(point_list, 3);
    free_pairs(pairs, num_pairs);
    free_points_pairs(points_pairs, num_points_pairs);

    return 0;
}*/
