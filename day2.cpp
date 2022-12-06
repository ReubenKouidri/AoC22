//
// Created by Juliette Kouidri on 02/12/2022.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "day2.hpp"


[[maybe_unused]] void print_map(const std::map<std::string, int>& m)
{
    for (const auto& [key, value] : m)
        std::cout << '[' << key << "] = " << value << "; ";

    std::cout << '\n';
}

// part 1
[[maybe_unused]] std::map<std::string, int> scoreMatrix {{"AX", 4}, {"AY", 8}, {"AZ", 3},
                                                         {"BX", 1}, {"BY", 5}, {"BZ", 9},
                                                         {"CX", 7}, {"CY", 2}, {"CZ", 6}};

// part 2
[[maybe_unused]] std::map<std::string, int> scoreMatrix2{{"AX", 0+3}, {"AY", 3+1}, {"AZ", 6+2},
                                                         {"BX", 0+1}, {"BY", 3+2}, {"BZ", 6+3},
                                                         {"CX", 0+2}, {"CY", 3+3}, {"CZ", 6+1}};


[[nodiscard]] int calcScore(const char c1, const char c2)
{
    auto c3 = std::string(1,c1)+c2;  // fills string with 1 character
    //return scoreMatrix[c3];  // for part 1
    return scoreMatrix2[c3];  // part 2
}

/*
 * #include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "day2.hpp"
 * int main()
{
    std::string filename{"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day2_data.txt"};
    std::ifstream file {};

    file.open(filename);
    if (file.fail())
    {
        std::cout << "Failed to open file " << filename << '\n';
        return 1;
    }


    std::string line {};
    int score {};
    char char1 {};
    char char2 {};

    while (std::getline(file, line))
    {
        std::stringstream ss;
        ss << line;  // e.g. "A X"
        ss >> char1 >> char2;  // e.g. char1 = 'A', char2 = 'X'
        score += calcScore(char1, char2);
    }

    file.close();

    std::cout << "Total score: " << score << '\n';

    return 0;
}
 */