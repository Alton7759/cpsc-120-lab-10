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
int RectangleArea(int length, int width) {
  int area{-1};
  area = width * length;
  if (width < 0 || length < 0) {
    area = 0;
  }
  std::cout << length << " x " << width << " = ";
  return area;
}
