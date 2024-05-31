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
List* create_list(int capacity) {
    List *list = (List*)malloc(sizeof(List));
    list->data = (int*)malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

// Fonction pour ajouter un élément à une liste dynamique
void add_to_list(List *list, int value) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
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
    free(list->data);
    free(list);
}

// Fonction qui implémente l'algorithme
List** process_matrix(int matrix[TAILLE][TAILLE]) {
    int index = 1;
    int taille = 1;
    List **list = (List**)malloc(TAILLE * sizeof(List*));
    list[0] = create_list(10);
    add_to_list(list[0], 1);

    List *Element = create_list(TAILLE); // Liste pour garder les éléments déjà ajoutés

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
                if (matrix[element - 1][j] == 1 && !contains(Element, j + 1)) {
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
void print_lists(List **lists) {
    for (int i = 0; i < TAILLE; i++) {
        printf("List %d: ", i);
        for (int j = 0; j < lists[i]->size; j++) {
            printf("%d ", lists[i]->data[j]);
        }
        printf("\n");
    }
}

/*int main() {
    int matrix[TAILLE][TAILLE] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0}
    };

    List **result = process_matrix(matrix);
    print_lists(result);

    // Free the allocated memory
    for (int i = 0; i < TAILLE; i++) {
        free_list(result[i]);
    }
    free(result);

    return 0;
}*/
