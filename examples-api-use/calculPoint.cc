#include <iostream>
#include <vector>
#include <cmath>
#include "decode_matrix.h"
// Structure pour représenter un point
struct Point {
    int longueur;
    int hauteur;
};

// Structure pour représenter une liste de points
struct PointList {
    std::vector<Point> points;
    int taille;
};




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
    list.points.resize(taille);
    list.taille = taille;
    return list;
}

// Fonction pour arrondir un nombre à l'entier inférieur
int arrondit_inferieur(float nombre) {
    return static_cast<int>(std::floor(nombre));
}

// Fonction pour créer une liste de points à partir d'une liste d'entiers
PointList* process_list(List** liste, int tailleH) {
    auto point_list = new PointList[tailleH];

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

int find_index(const std::vector<int>& list, int number) {
    auto it = std::find(list.begin(), list.end(), number);
    if (it != list.end()) {
        return std::distance(list.begin(), it);
    }
    return -1;
}

// Fonction pour libérer la mémoire d'une liste de points
void free_point_list(PointList *point_list, int taille) {
    for (int i = 0; i < taille; i++) {
        delete[] point_list[i].points.data();
    }
    delete[] point_list;
}

// Fonction pour afficher une liste de points
void print_point_list(PointList *point_list, int taille) {
    for (int i = 0; i < taille; i++) {
        std::cout << "List " << i << ":\n";
        for (int j = 0; j < point_list[i].taille; j++) {
            std::cout << "Point " << j << ": Longueur = " << point_list[i].points[j].longueur << ", Hauteur = " << point_list[i].points[j].hauteur << "\n";
        }
        std::cout << "\n";
    }
}

/*int main() {
    // Exemple de liste d'entiers
    List* liste_entiers[3];
    liste_entiers[0] = create_list(2);
    liste_entiers[1] = create_list(2);
    liste_entiers[2] = create_list(2);

    liste_entiers[0]->data[0] = 1;
    liste_entiers[1]->data[0] = 2;
    liste_entiers[1]->data[1] = 3;
    liste_entiers[2]->data[0] = 2;
    liste_entiers[2]->data[1] = 5;
    liste_entiers[0]->size = 1;
    liste_entiers[1]->size = 2;
    liste_entiers[2]->size = 2;

    // Création de la liste de points
    PointList *point_list = process_list(liste_entiers, 3);

    // Affichage de la liste de points
    print_point_list(point_list, 3);

    // Libération de la mémoire
    free_point_list(point_list, 3);

    // Libération de la mémoire des listes
    for (int i = 0; i < 3; i++) {
        free_list(liste_entiers[i]);
    }

    return 0;
}*/
