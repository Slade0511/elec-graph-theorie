#ifndef CREATELINE_H
#define CREATELINE_H

#include <vector>
#include <utility>

// Structure pour représenter un point
struct Point {
    int longueur;
    int hauteur;
};

// Structure pour représenter une liste de points
struct PointList {
    std::vector<Point> points;
};

// Fonction pour trouver l'index d'un numéro dans une liste

// Fonction pour convertir les paires de numéros en paires de points
std::vector<std::pair<Point, Point>> find_connected_points(const std::vector<std::vector<int>>& matrix,
                                                           const std::vector<PointList>& point_lists);

// Fonction pour afficher les paires de points
void print_connected_points(const std::vector<std::pair<Point, Point>>& connected_points);

#endif // CREATELINE_H
