#include "led-matrix.h"

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <vector>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
  interrupt_received = true;
}

static void DrawOnCanvas(Canvas *canvas, const std::vector<std::vector<int>>& matrix) {
  // Clear the canvas to start with a blank display
  canvas->Clear();

  // Define the color for the LEDs
  rgb_matrix::Color blue_color(0, 0, 255);     // Blue color for '1'

  // Draw the LED matrix based on the values in the matrix
  for (int y = 0; y < canvas->height(); ++y) {
    for (int x = 0; x < canvas->width(); ++x) {
      // Check if the corresponding value in the matrix is '1'
      if (matrix[y][x] == 1) {
        // If '1', set the LED at position (x, y) to blue_color
        canvas->SetPixel(x, y, 0, 0, 255);
      }
    }
  }

  // Wait for a short period to display the matrix
  usleep(1 * 1000000);
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

  // Set up signal handlers
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  // Define the matrix 32x32 with '1's and '0's (you can adjust this matrix as needed)
  std::vector<std::vector<int>> matrix(32, std::vector<int>(32, 1)); // Initialize a 32x32 matrix with all '0's

  // Manually set some '1's in the matrix (for example)
  matrix[0][0] = 1;
  matrix[31][0] = 1;
  matrix[0][31] = 1;
  matrix[31][31] = 1;

  // Display the matrix on the canvas
  DrawOnCanvas(canvas, matrix);

  // Animation finished. Clear the canvas and shut down the RGB matrix.
  canvas->Clear();
  delete canvas;

  return 0;
}
