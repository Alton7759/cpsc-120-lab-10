// Christian Alton bonilla
// CPSC 120-01
// 2022-11-14
// Alton77@csu.fullerton.edu
// @alton7759
//
// Lab 10-02
// Partners: @annavera38
//
// make sure things conncet
//

/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#ifndef COUNTIES_FUNCTIONS_H
#define COUNTIES_FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>

std::string AllCountiesString(
    const std::vector<std::vector<std::string>>& ca_counties);

int CountyIndex(const std::vector<std::vector<std::string>>& ca_counties,
                const std::string& match_county);

#endif