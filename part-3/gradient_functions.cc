// TODO: Insert your own header

#include "gradient_functions.h"

// The function returns true if file_name ends with extension.
// For example, the function will return true if the file_name is
// "output_image.png" and extension is ".png". The function will
// return false if file_name is "output_image.bmp" and extension is
// ".png".
bool HasMatchingFileExtension(const std::string& file_name,
                              const std::string& extension) {
  // TODO: Implement this function.
  // Check if the length of the file_name is greater than
  // or equal to the length of extension and compare if file_name ends
  // with the extension using the compare member function, see
  // https://en.cppreference.com/w/cpp/string/basic_string/compare
  // Hint: Use file_name's compare member function:
  //      file_name.compare()
  // It will take three parameters.
  // The first parameter is where you want to start comparing.
  // Mathematically, this is the length of file_name minus the length
  // of extension.
  // The second parameter is how many letters you want to check
  // which is the length of extension.
  // The third parameter is what you want to compare file_name to,
  // which is extension.
  // Remember that file_name.compare() returns 0 if the comparison
  // is true. This means you will want to use the 'equal to' operator
  // '==' to check to see if file_name.compare() returned 0.
  // ex. file_name.compare() == 0
  return false;
}
