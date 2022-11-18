// Christian Alton bonilla
// CPSC 120-01
// 2022-11-17
// Alton77@csu.fullerton.edu
// @alton7759
//
// Lab 10-03
// Partners: @annavera38
//
// checks if the extensions are the same
//

#include "gradient_functions.h"

bool HasMatchingFileExtension(const std::string& file_name,
                              const std::string& extension) {
  return file_name.size() >= extension.size() &&
         (file_name.compare(file_name.size() - extension.size(),
                            extension.size(), extension) == 0);
}
