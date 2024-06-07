#include <iostream>
#include <vector>
#include <cmath>

// Fonction pour trouver l'index d'un nombre dans une liste de listes d'entiers
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

// Structure pour représenter un point avec une liste de noms
struct Point {
    int longueur;
    int hauteur;
};

// Structure pour représenter une liste de points
struct PointList {
    std::vector<Point> points;
};





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

void print_point_pairs(const std::vector<std::vector<Point>>& points) {
    std::cout << "[";
    for (size_t i = 0; i < points.size(); ++i) {
        const auto& pair = points[i];
        std::cout << "[(" << pair[0].longueur << "," << pair[0].hauteur << "), "
                  << "(" << pair[1].longueur << "," << pair[1].hauteur << ")]";
        if (i < points.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    // Matrice originale
    std::vector<std::vector<int>> matrix = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0}
    };

    std::vector<std::vector<int>> listName = {
            {1},
            {2,3},
            {4,5}
        };

    // Liste des points avec les noms correspondants
    std::vector<std::vector<Point>> ListPoint = {
        {Point{16, 27}},
        {Point{8, 17}, Point{24, 17}},
        {Point{8, 7}, Point{24, 7}}
    };


    // Trouver les points connectés
    std::vector<std::vector<Point>> filledList = fill_list(matrix, listName, ListPoint);

        // Afficher la liste de paires de points
        std::cout << "Liste de paires de points :" << std::endl;
        for (const auto& pair : filledList) {
            std::cout << "[(" << pair[0].longueur << ", " << pair[0].hauteur << "), (" << pair[1].longueur << ", " << pair[1].hauteur << ")]" << std::endl;
        }
    return 0;
}
