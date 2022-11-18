// Christian Alton bonilla
// CPSC 120-01
// 2022-11-17
// Alton77@csu.fullerton.edu
// @alton7759
//
// Lab 10-03
// Partners: @annavera38
//
// makes gradient
//

#include <Magick++.h>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gradient_functions.h"

const int kImageWidth{512};
const int kImageHeight{512};

int main(int argc, char* argv[]) {
  Magick::InitializeMagick(*argv);
  std::vector<std::string> arguments(argv, argv + argc);

  if (arguments.size() < 2) {
    std::cout << "Please provide a path to a file.\n";
    return 1;
  }
  std::string output_file_name{arguments.at(1)};
  std::string image_format{".png"};
  if (!HasMatchingFileExtension(output_file_name, image_format)) {
    std::cout << arguments.at(1) << " is missing the required file extension "
              << image_format << ".\n";
    return 1;
  }
  Magick::ColorRGB white(1, 1, 1);
  Magick::Image image(Magick::Geometry(kImageWidth, kImageHeight), white);

  for (int column = int(image.columns() - 1); column >= 0; column--) {
    for (int row = 0; row < image.rows(); row++) {
      double red = double(row) / double(image.rows() - 1);
      double green = double(column) / double(image.columns() - 1);
      double blue = 0.25;
      Magick::ColorRGB color{red, green, blue};
      image.pixelColor(row, column, color);
    }
  }
  image.write(output_file_name);
  return 0;
}
