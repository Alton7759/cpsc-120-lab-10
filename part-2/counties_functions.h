// TODO: Insert your own header

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