// Christian Alton bonilla
// CPSC 120-01
// 2022-11-14
// Alton77@csu.fullerton.edu
// @alton7759
//
// Lab 10-01
// Partners: @annavera38
//
// some functons
//

#include "counties_functions.h"

std::string AllCountiesString(
    const std::vector<std::vector<std::string>>& ca_counties) {
  std::string all_counties_string;
  int loc{0};
  std::string space{" "};
  for (const std::string& add : ca_counties.at(0)) {
    all_counties_string.insert(loc, add);
    loc += add.size();
    all_counties_string.insert(loc, space);
    loc += space.size();
  }
  return all_counties_string;
}

int CountyIndex(const std::vector<std::vector<std::string>>& ca_counties,
                const std::string& match_county) {
  int index{-1};
  int locofmatch{-1};
  for (const std::string& checker : ca_counties.at(0)) {
    index++;
    if (checker == match_county) {
      locofmatch = index;
      break;
    }
  }
  return locofmatch;
}
