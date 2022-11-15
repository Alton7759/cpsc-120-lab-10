// Christian Alton bonilla
// CPSC 120-01
// 2022-11-14
// Alton77@csu.fullerton.edu
// @alton7759
//
// Lab 10-01
// Partners: @annavera38
//
// Calculate the area of a triangle defined by length and width.
//

#include <iostream>
#include <string>
#include <vector>

#include "rectangle_area_functions.h"

int main(int argc, char const* argv[]) {
  std::vector<std::string> arguments(argv, argv + argc);
  std::vector<std::string> numbers{"-", "1", "2", "3", "4", "5",
                                   "6", "7", "8", "9", "0"};
  if (arguments.size() == 3) {
    arguments.erase(arguments.begin());
  } else {
    std::cout << "Please provide two arguments, a rectangle's length and "
                 "width.";
    return 1;
  }
  bool isnum = false;
  for (const std::string& check : numbers) {
    isnum = false;
    std::string word{arguments.at(0).at(0)};
    if (word == check) {
      isnum = true;
      break;
    }
  }
  bool isnum2 = false;
  for (const std::string& check2 : numbers) {
    isnum2 = false;
    std::string word2{arguments.at(1).at(0)};
    if (word2 == check2) {
      isnum2 = true;
      break;
    }
  }
  if (isnum && isnum2) {
    int length{std::stoi(arguments.at(0))};
    int width{std::stoi(arguments.at(1))};
    std::cout << RectangleArea(length, width);
  } else {
    std::cout << "There was a problem reading the input numbers.";
    return 1;
  }

  return 0;
}