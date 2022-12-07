#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "day3.hpp"


int main()
{
    std::string filename{"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day3_data.txt"};
    std::ifstream file {};

    file.open(filename);
    if (file.fail()){
        std::cout << "Failed to open file " << filename << '\n';
        return 1;
    }

    std::string line {};
    std::vector<std::string> v {};

    while (std::getline(file, line))
    {
        std::stringstream ss;
        ss << line;
        v.emplace_back(line);
    }

    // part 2 --------------------------------
    std::vector<std::vector<std::string>> triples = SplitVector(v, 3);

    int sumPriorities {};
    for (const auto& triple : triples){
        sumPriorities += calcPriority(triple);
    }
    std::cout << "Priority: " << sumPriorities << '\n';
    // ------------------------------------------------------



    /*// part 1----------------------------------------------
    int sum {};
    while (std::getline(file, line))
    {
        std::stringstream ss;
        ss << line;  // e.g. "AjfuHndhTL"
        std::string firstHalf{line.substr(0, line.length() / 2)};
        std::string secondHalf{line.substr(line.length() / 2)};

        unsigned char shared = findSharedChar(firstHalf, secondHalf);
        sum += convertCharToRange(shared);
    }
    std::cout << sum << '\n';
    */// ----------------------------------------------------

    file.close();
    return 0;
}
