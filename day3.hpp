//
// Created by Juliette Kouidri on 05/12/2022.
//

#ifndef AOC22_DAY3_HPP
#define AOC22_DAY3_HPP

#include <iostream>
#include <string>

#define VVS_t std::vector<std::vector<std::string>>

[[nodiscard]] [[nodiscard]] int convertCharToRange(unsigned char c);

[[maybe_unused]] [[nodiscard]] unsigned char findSharedChar(const std::string& s1, const std::string& s2);

[[maybe_unused]] [[nodiscard]] int findSharedChar(const std::vector<std::string>& vec);

[[maybe_unused]] [[nodiscard]] int calcPriority(const std::vector<std::string>& vec);

VVS_t SplitVector(const std::vector<std::string>& vec, int n);


#endif //AOC22_DAY3_HPP
