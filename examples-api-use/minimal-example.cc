// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include "led-matrix.h"

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <vector>
#include <utility>
#include "createMatrixPrint"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

// Function to create a 32x32 matrix from a list of coordinates
void CreateMatrixFromCoordinates(const std::vector<std::pair<int, int>>& coordinates, int matrix[32][32]) {
  // Clear the matrix
  for (int y = 0; y < 32; ++y) {
    for (int x = 0; x < 32; ++x) {
      matrix[y][x] = 0;
    }
  }

  // Set the pixels based on the coordinates
  for (const auto& coord : coordinates) {
    int x = coord.first;
    int y = coord.second;
    if (x >= 0 && x < 32 && y >= 0 && y < 32) {
      matrix[y][x] = 1;
    }
  }
}

int MaxOnesInRow(const std::vector<std::vector<int>>& matrix) {
  int max_ones = 0;

  for (const auto& row : matrix) {
    int count = std::count(row.begin(), row.end(), 1);  // Count the number of 1s in the current row
    max_ones = std::max(max_ones, count);  // Update the maximum count if current count is higher
  }

  return max_ones;
}

static void DrawOnCanvas(Canvas *canvas, const int matrix[32][32]) {
  for (int y = 0; y < 32; ++y) {
    for (int x = 0; x < 32; ++x) {
      if (matrix[y][x] == 1) {
        canvas->SetPixel(x, y, 255, 0, 0);  // Turn on the LED (red color)
      } else {
        canvas->SetPixel(x, y, 0, 0, 0);    // Turn off the LED
      }
    }
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

  // Define the list of coordinates
  std::vector<std::pair<int, int>> coordinates = {
    {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7},
    {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15},
    {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}, {23, 23},
    {24, 24}, {25, 25}, {26, 26}, {27, 27}, {28, 28}, {29, 29}, {30, 30}, {31, 31}
  };

  // Define the 32x32 matrix
  int matrix32x32[32][32];

  // Create the 32x32 matrix from the list of coordinates
  CreateMatrixFromCoordinates(coordinates, result);

  // Draw the 32x32 matrix on the canvas
  DrawOnCanvas(canvas, matrix32x32);

  // Wait indefinitely
  while (true) {
    usleep(1000 * 1000);  // Sleep for 1 second intervals to keep the program running.
  }

  // Cleanup (This part will never be reached in this version, but kept for completeness)
  canvas->Clear();
  delete canvas;

  return 0;
}
