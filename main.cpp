#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <algorithm>


template<typename T>
std::vector<T> arange(T start, T stop, T step = 1)
{
    std::vector<T> values {};
    for (T value = start; value < stop; value += step){
        values.template emplace_back(value);
    }
}


int main()
{
    std::string filename{"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day4_test.txt"};
    std::ifstream file {};

    file.open(filename);
    if (file.fail()){
        std::cout << "Failed to open file " << filename << '\n';
        return 1;
    }

    std::string line {};
    std::stringstream ss;
    char n1, n2, n3, n4;

    while (std::getline(file, line, ','))
    {
        std::cout << line << '\n';
        line.erase(std::remove(line.begin(), line.end(), '-'), line.end());
        //std::cout << line << "endl" << '\n';
        ss << line;
        //ss >> n1 >> n2;
        //std::cout << n1 << ", " << n2 << '\n';
    }

    file.close();
    return 0;
}
