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
    int x;
    int y;
};

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

  // Définition de la liste de points
  std::vector<Point> points = {{3, 3}, {8, 10}, {15, 20}, {16, 16}, {22, 8}};

  // Dessine des lignes en boucle
  while (!interrupt_received) {
      // Dessine des lignes entre chaque paire de points consécutifs
      for (size_t i = 0; i < points.size() - 1; ++i) {
          DrawLine(canvas, points[i], points[i + 1], 255, 0, 0);
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
