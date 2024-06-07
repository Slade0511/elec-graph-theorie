#include <stdio.h>
#include "createLine.h"
#include "decode_matrix.h"
#include "calculPoint.h"
#include "led_matrix_runner.h"

#define TAILLE 5
#define DIM 32

int main() {
    // Matrice d'origine
   /* int matrix[TAILLE][TAILLE] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0}
    };*/

    int matrix[TAILLE][TAILLE] = {
            {0, 1, 0, 0, 0},
            {1, 0, 1, 1, 1},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 1, 0, 0, 0}
        };

    // Exemple de liste d'entiers
    List **result = process_matrix(matrix);

    int taille = 0;
            while (result[taille] != NULL) {
                taille++;
            }

    print_lists(result, taille);

        // Free the allocated memory


    // Création de la liste de points
       PointList *point_list = process_list(result, 3);

       // Affichage de la liste de points
       print_point_list(point_list, 3);

       // Libération de la mémoire

    // Trouver les paires de numéros qui se croisent sans doublons
    int num_pairs;
    int** pairs = find_crossing_pairs(matrix, TAILLE, &num_pairs);

    // Afficher les paires de numéros
    printf("Paires de numéros :\n");
    print_pairs(pairs, num_pairs);
    printf("\n");

    // Convertir les paires de numéros en paires de points
    int num_points_pairs;
    Point** points_pairs = convert_pairs_to_points(pairs, num_pairs, point_list, result, &num_points_pairs);

    // Afficher les paires de points
    printf("Paires de points :\n");
    print_points_pairs(points_pairs, num_points_pairs);
    printf("\n");

    // Initialisation de la matrice 32x32
    static int result_matrix[DIM][DIM];
    init_matrix(result_matrix);

    // Placer et relier les points dans la matrice 32x32
    place_and_connect_points(points_pairs, num_points_pairs, result_matrix);
    // Affichage de la matrice 32x32
    printf("Matrice résultante 32x32 :\n");
    print_matrix(result_matrix);
    printf("\n");

    RunMatrix(matrix);

    free_point_list(point_list, 3);

    // Libération de la mémoire
    free_point_list(point_list, 3);
    free_pairs(pairs, num_pairs);
    free_points_pairs(points_pairs, num_points_pairs);

    for (int i = 0; i < TAILLE; i++) {
                free_list(result[i]);
            }
            free(result);

    return 0;
}
