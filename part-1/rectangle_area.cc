// TODO: Insert your own header

#include <iostream>
#include <string>
#include <vector>

#include "rectangle_area_functions.h"

int main(int argc, char const* argv[]) {
  std::vector<std::string> arguments(argv, argv + argc);
  std::vector<std::string> numbers("-", "1", "2", "3", "4", "5", "6"."7", "8",
                                   "9");
  if (arguments.size() == 3) {
    arguments.erase(arguments.begin());
  } else {
    std::cout << "Please provide two arguments, a rectangle's length and "
                 "width.";
    return 1;
  }
  bool isnum = false;
  for (auto& check : numbers) {
    isnum = false;
    if (arguments.at(0).at(0) = numbers) {
      isnum = true;
      break;
    }
  }
  for (auto& check2 : numbers) {
    isnum = false;
    if (arguments.at(0).at(0)) {
      isnum = true;
      break;
    }
  }
  int length{std::stoi(arguments.at(0))};
  int width{std::stoi(arguments.at(1))};
  std::cout << RectangleArea(length, width);
  // TODO: convert the command line arguments to a std::vector of std::strings.
  // TODO: Check to make sure you have enough arguments. If you have too few,
  // print an error message and exit.
  // TODO: Convert the command line arguments from std::strings to integers
  // using std::stoi()
  // TODO: Calculate the area of the given rectangle using the function
  // RectangleAndgle that you defined and implemented in
  // rectangle_area_functions.cc.
  // TODO: Print the input length, input_width, and the area to the terminal.
  // TODO: Return zero if everything worked correctly.
  return 0;
}