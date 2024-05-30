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

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

static void DrawOnCanvas(Canvas *canvas) {
  /*
   * We simply fill the entire canvas with a color.
   */
  canvas->Fill(255, 0, 0);  // Fill the entire matrix with red color (255, 0, 0)
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

  DrawOnCanvas(canvas);  // Using the canvas.

  // Wait indefinitely
  while (true) {
    usleep(1000 * 1000);  // Sleep for 1 second intervals to keep the program running.
  }

  // Cleanup (This part will never be reached in this version, but kept for completeness)
  canvas->Clear();
  delete canvas;

  return 0;
}
