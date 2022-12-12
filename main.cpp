#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


template<typename T>
void printVector(const std::vector<T>& vec){
    for (const auto i : vec){
        std::cout << ' ' << i << ' ';
    }
    std::cout << '\n';
}

template<typename T>
void moveItems(size_t num, std::vector<T> &fromStack, std::vector<T> &toStack)
{
    for (size_t i = num; i > 0; i--){
        toStack.emplace_back(fromStack.back());
        fromStack.pop_back();
    }
}

/*

int main()
{
    const size_t numStacks = 9;
    std::ifstream cratesFile("inputs/d5.txt");
    std::string cratesLine;
    std::vector<char> crates[numStacks];

    while (getline(cratesFile, cratesLine)) {
        if (cratesLine.substr(1, 1) == "1") break;
        for (size_t i = 0; i < numStacks; i++) {
            if (cratesLine.substr(4*i + 1, 1) == " ") continue;
            crates[i].push_back(cratesLine[4*i + 1]);
        }
    }

    for (size_t i = 0; i < numStacks; i++)
        std::reverse(crates[i].begin(), crates[i].end());

    size_t num, from, to;
    std::string blank;
    while (cratesFile >> blank >> num >> blank >> from >> blank >> to) {
        move(num, crates[from - 1], crates[to - 1]);
    }

    for (size_t i = 0; i < numStacks; i++)
        std::cout << crates[i].back();
    std::cout << "\n";
}

*/

int main()
{
    std::string filename{"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day5/day5_test.txt"};
    std::ifstream file {};

    file.open(filename);
    if (file.fail()){
        std::cout << "Failed to open file " << filename << '\n';
        return 1;
    }

    //std::string chars = "[]";
    //std::string line {};

    //while (std::getline(file, line))
    //{
    //    std::stringstream ss;
    //    ss << line;
    //    for (const auto c: chars) {
    //        std::replace(line.begin(), line.end(), c, ' ');
    //    }
    //    std::cout << line << '\n';
    //}

    //file.close();
    return 0;
}
