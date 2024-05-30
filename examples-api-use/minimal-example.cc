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
#include <cmath>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

// Function to draw a line between two points on the 32x32 matrix
void DrawLine(int x0, int y0, int x1, int y1, int matrix[32][32]) {
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2;

  while (true) {
    matrix[y0][x0] = 1;
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; }
    if (e2 <= dx) { err += dx; y0 += sy; }
  }
}

// Function to convert a planar graph 8x8 matrix to a 32x32 matrix
void Convert8x8To32x32(const int input[8][8], int output[32][32]) {
  // Clear the output matrix
  for (int y = 0; y < 32; ++y) {
    for (int x = 0; x < 32; ++x) {
      output[y][x] = 0;
    }
  }

  // Define the scaling factor and offsets
  int scale = 4;
  int offset = 2;

  // Draw nodes and connections
  for (int y = 0; y < 8; ++y) {
    for (int x = 0; x < 8; ++x) {
      if (input[y][x] == 1) {
        int x0 = x * scale + offset;
        int y0 = y * scale + offset;
        output[y0][x0] = 1;  // Draw the node

        // Connect to the right node
        if (x < 7 && input[y][x + 1] == 1) {
          int x1 = (x + 1) * scale + offset;
          int y1 = y * scale + offset;
          DrawLine(x0, y0, x1, y1, output);
        }

        // Connect to the bottom node
        if (y < 7 && input[y + 1][x] == 1) {
          int x1 = x * scale + offset;
          int y1 = (y + 1) * scale + offset;
          DrawLine(x0, y0, x1, y1, output);
        }
      }
    }
  }
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

  // Define the 8x8 matrix
  int matrix8x8[8][8] = {
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 1}
  };

  // Define the 32x32 matrix
  int matrix32x32[32][32];

  // Convert the 8x8 matrix to the 32x32 matrix
  Convert8x8To32x32(matrix8x8, matrix32x32);

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
