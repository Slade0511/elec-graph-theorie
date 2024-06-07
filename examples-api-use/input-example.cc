#include "led-matrix.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <vector>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

// Structure pour représenter un point
struct Point {
    int longueur;
    int hauteur;
};

// Fonction pour afficher les points en reliant ceux de chaque élément de la même sous-liste
void display_points(const std::vector<std::vector<Point>>& points, RGBMatrix *matrix) {
    while (!interrupt_received) {
        for (const auto& sublist : points) {
            // Connecter les points de chaque sous-liste
            for (size_t i = 0; i < sublist.size() - 1; ++i) {
                int x1 = sublist[i].longueur;
                int y1 = sublist[i].hauteur;
                int x2 = sublist[i + 1].longueur;
                int y2 = sublist[i + 1].hauteur;

                // Dessiner une ligne entre les points (x1, y1) et (x2, y2)
                for (int x = x1; x <= x2; ++x) {
                    int y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
                    matrix->SetPixel(x, y, 255, 255, 255); // Blanc
                }
            }
        }

        // Ajouter un petit délai pour réduire l'utilisation du processeur
        usleep(100000);  // 100 ms
    }
}

int main(int argc, char *argv[]) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
    defaults.rows = 32;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    RGBMatrix *matrix = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (matrix == NULL)
        return 1;

    // It is always good to set up a signal handler to cleanly exit when we
    // receive a CTRL-C for instance.
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    // Liste de points
    std::vector<std::vector<Point>> points = {
        {{1, 1}, {5, 5}, {10, 15}}, // Première sous-liste
        {{2, 2}, {6, 6}, {20, 10}}   // Deuxième sous-liste, etc.
        // Ajoutez d'autres sous-listes au besoin
    };

    // Afficher les points en reliant ceux de chaque élément de la même sous-liste
    display_points(points, matrix);

    fprintf(stderr, "Exiting.\n");
    matrix->Clear();
    delete matrix;

    return 0;
}
