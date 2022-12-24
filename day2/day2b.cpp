#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>


[[maybe_unused]] void print_map(const std::map<std::string, size_t>& m){
    for (const auto& [key, value] : m)
        std::cout << '[' << key << "] = " << value << "; ";
    std::cout << '\n';
}

std::map<std::string, size_t> scoreMatrix{{"AX", 0+3}, {"AY", 3+1}, {"AZ", 6+2},
                                          {"BX", 0+1}, {"BY", 3+2}, {"BZ", 6+3},
                                          {"CX", 0+2}, {"CY", 3+3}, {"CZ", 6+1}};


[[nodiscard]] size_t calcScore(const char c1, const char c2){
    auto c3 = std::string(1,c1) + c2;  // creates a string "c1c2" e.g. "AY" from 'A' 'Y'
    return scoreMatrix[c3];
}


int main() {
    std::ifstream file {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day2/day2_data.txt"};

    std::string line {};
    size_t score {};
    char char1 {};
    char char2 {};

    while (std::getline(file, line) && !file.fail()) {
        std::stringstream ss;
        ss << line;  // e.g. "A X"
        ss >> char1 >> char2;  // e.g. char1 = 'A', char2 = 'X'
        score += calcScore(char1, char2);
    }

    std::cout << "Total score: " << score << '\n';
    return 0;
}
