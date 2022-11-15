// TODO: Insert your own header

#include "counties_functions.h"

std::string AllCountiesString(
    const std::vector<std::vector<std::string>>& ca_counties) {
  std::string all_counties_string;
  // TODO: Implement the function
  // Write a loop which takes the name of each county from the vector
  // ca_counties and adds it to all_counties_string along with a space.
  return all_counties_string;
}

int CountyIndex(const std::vector<std::vector<std::string>>& ca_counties,
                const std::string& match_county) {
  int index{-1};
  // TODO: Implement the function
  // Write a loop which goes through the ca_counties vector looking
  // for a match with the string match_county. When it finds a match,
  // return the index of the match. If it is not found, return -1.
  return index;
}
