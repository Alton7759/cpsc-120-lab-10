// Julianna Vera
// CPSC 120-01
// 14-11-2022
// annavera38@csu.fullerton.edu
// @annavera38
//
// Lab 10-01
// Partners: @alton7759
//
// Calculate the area of a triangle defined by length and width.
#include <iostream>
int RectangleArea(int length, int width) {
  int area{-1};
  area = width * length;
  if (width < 0 || length < 0) {
    area = 0;
  }
  std::cout << length << " x " << width << " = ";
  return area;
}
