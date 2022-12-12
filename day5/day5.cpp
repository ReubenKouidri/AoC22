//
// Created by Reuben Kouidri on 08/12/2022.
//

#include "day5.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>


template<typename T>
void moveItems(size_t num, std::vector<T> &fromStack, std::vector<T> &toStack)
{
    for (size_t i = num; i > 0; i--){
        toStack.emplace_back(fromStack.back());
        fromStack.pop_back();
    }
}

template<typename T>
void moveItemsPart2(size_t num, std::vector<T>& fromStack, std::vector<T>& toStack)
{
    const size_t idx {fromStack.size() - num};
    for (size_t i = 0; i < num; i++){
        toStack.emplace_back(fromStack[idx]);
        fromStack.erase(fromStack.begin() + idx);
    }
}


int main()
{
    std::string filename{"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day5/day5_data.txt"};
    std::ifstream file {};

    file.open(filename);
    if (file.fail()){
        std::cout << "Failed to open file " << filename << '\n';
        return 1;
    }

    std::string line {};
    constexpr size_t numStacks { 9 };
    std::vector<char> crateStacks [numStacks] {};

    while (std::getline(file, line))
    {
        if (line.substr(1, 1) == "1") break;
        for (size_t i = 0; i < numStacks; i++){
            if (line.length() > 4 * i && line.substr(4 * i + 1, 1) == " ") continue;
            crateStacks[i].emplace_back(line[4*i + 1]);
        }
    }

    for (auto& stack : crateStacks) {
        std::reverse(stack.begin(), stack.end());
    }

    size_t num {};
    size_t from {};
    size_t to {};
    std::string filler {};

    while (file >> filler >> num >> filler >> from >> filler >> to)
        moveItemsPart2(num, crateStacks[from - 1], crateStacks[to - 1]);

    for (const auto& crateStack : crateStacks){
        std::cout << crateStack.back();
    }
    std::cout << '\n';
    file.close();
    return 0;
}


