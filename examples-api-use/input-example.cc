#include "led-matrix.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <vector>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

#define TAILLE 5

struct Point {
    int x;
    int y;
};

// Structure pour une liste dynamique
typedef struct {
    int *data;
    int size;
    int capacity;
} List;

// Structure pour représenter une liste de points
struct PointList {
    std::vector<Point> points;
    int taille;
};

std::vector<int> find_index(const std::vector<std::vector<int>>& list, int number) {
    std::vector<int> result(2, -1); // Initialiser avec des valeurs par défaut

    for (size_t i = 0; i < list.size(); ++i) {
        for (size_t j = 0; j < list[i].size(); ++j) {
            if (list[i][j] == number) {
                result[0] = i; // Indice de la sous-liste
                result[1] = j; // Indice de l'élément dans la sous-liste
                return result;
            }
        }
    }

    return result; // Renvoyer {-1, -1} si l'élément n'est pas trouvé
}

std::vector<std::vector<Point>> fill_list(const std::vector<std::vector<int>>& matrix,
                                          const std::vector<std::vector<int>>& listName,
                                          const std::vector<std::vector<Point>>& ListPoint) {
    std::vector<std::vector<Point>> result;

    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == 1) {
                // Trouver les indices des points dans la liste de noms
                int xi = find_index(listName, i + 1)[0];
                int yi = find_index(listName, i + 1)[1];
                int xj = find_index(listName, j + 1)[0];
                int yj = find_index(listName, j + 1)[1];

                // Ajouter la paire de points correspondante à la liste résultat
                result.push_back({ListPoint[xi][yi], ListPoint[xj][yj]});
            }
        }
    }

    return result;
}

// Fonction pour initialiser une liste dynamique
List* create_list(int capacity) {
    List *list = (List*)malloc(sizeof(List));
    if (!list) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la liste\n");
        exit(EXIT_FAILURE);
    }
    list->data = (int*)malloc(capacity * sizeof(int));
    if (!list->data) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour les données de la liste\n");
        free(list);
        exit(EXIT_FAILURE);
    }
    list->size = 0;
    list->capacity = capacity;
    return list;
}

// Fonction pour ajouter un élément à une liste dynamique
void add_to_list(List *list, int value) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
        if (!list->data) {
            fprintf(stderr, "Erreur de réallocation de mémoire pour les données de la liste\n");
            free(list);
            exit(EXIT_FAILURE);
        }
    }
    list->data[list->size++] = value;
}

// Fonction pour vérifier si une liste contient un élément
int contains(List *list, int value) {
    for (int i = 0; i < list->size; i++) {
        if (list->data[i] == value) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour libérer la mémoire d'une liste dynamique
void free_list(List *list) {
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

// Fonction qui implémente l'algorithme
List** process_matrix(int matrix[TAILLE][TAILLE]) {
    int index = 1;
    int taille = 1;
    List **list = (List**)malloc(TAILLE * sizeof(List*));
    if (!list) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la liste de listes\n");
        exit(EXIT_FAILURE);
    }
    list[0] = create_list(10);
    add_to_list(list[0], 1);

    List *Element = create_list(TAILLE); // Liste pour garder les éléments déjà ajoutés
    if (!Element) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la liste Element\n");
        exit(EXIT_FAILURE);
    }

    // Initialiser la liste Element avec les éléments de la première liste
    for (int i = 0; i < list[0]->size; i++) {
        add_to_list(Element, list[0]->data[i]);
    }

    while (taille < TAILLE) {
        List *current_list = list[index - 1];
        List *new_list = create_list(10);

        for (int nb = 0; nb < current_list->size; nb++) {
            int element = current_list->data[nb];
            for (int j = 0; j < TAILLE; j++) {
                if (matrix[element - 1][j] == 1 && !contains(Element, j + 1) && !contains(new_list, j + 1)) {
                    add_to_list(new_list, j + 1);
                    add_to_list(Element, j + 1); // Ajouter l'élément à la liste Element
                    taille++;
                }
            }
        }

        list[index] = new_list;
        index++;
    }

    free_list(Element); // Libérer la mémoire de la liste Element

    return list;
}

// Fonction pour imprimer les listes
void print_lists(List **lists, int taille) {
    for (int i = 0; i < taille; i++) {
        if (lists[i] == NULL) {
            fprintf(stderr, "Liste %d est NULL\n", i);
            continue;
        }
        printf("List %d: ", i);
        for (int j = 0; j < lists[i]->size; j++) {
            printf("%d ", lists[i]->data[j]);
        }
        printf("\n");
    }
}

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

// Fonction pour dessiner une ligne entre deux points
void DrawLine(Canvas *canvas, const Point& p1, const Point& p2, uint8_t r, uint8_t g, uint8_t b) {
    // Calcul des deltas
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);

    // Déterminer les incréments
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;

    // Initialiser les variables de décision
    int err = dx - dy;
    int e2;

    // Coordonnées actuelles
    int x = p1.x;
    int y = p1.y;

    // Boucle de tracé
    while (true) {
        // Dessiner le pixel actuel
        canvas->SetPixel(x, y, r, g, b);

        // Vérifier si nous avons atteint la destination
        if (x == p2.x && y == p2.y) break;

        // Calculer la prochaine étape
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx) { err += dx; y += sy; }
    }
}

int main(int argc, char *argv[]) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
    defaults.rows = 32;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.show_refresh_rate = true;
    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL)
        return 1;

    // It is always good to set up a signal handler to cleanly exit when we
    // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
    // for that.
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    std::vector<std::vector<int>> matrix = {
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 1, 0, 0}
    };

    std::vector<std::vector<int>> listName = {
        {1,2,3},
        {4, 5},
    };

    // Liste des points avec les noms correspondants
    std::vector<std::vector<Point>> ListPoint = {
        {{5, 27}, {15, 27}, {25, 27}},
        { {8, 17}, {24, 17} },
    };

    // Trouver les points connectés
    std::vector<std::vector<Point>> filledList = fill_list(matrix, listName, ListPoint);

    // Définition de la liste de points

    // Dessine des lignes en boucle
    while (!interrupt_received) {
        // Dessine des lignes entre chaque paire de points dans filledList
        for (const auto& pair : filledList) {
            DrawLine(canvas, pair[0], pair[1], 255, 0, 0);
        }

        // Attends un moment avant de recommencer
        usleep(5 * 1000000);  // Attend 5 secondes

        // Efface le canevas pour la prochaine itération
        canvas->Clear();
    }

    // Nettoie et quitte
    delete canvas;

    return 0;
}
