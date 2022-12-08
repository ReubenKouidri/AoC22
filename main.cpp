#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <algorithm>


template<typename T>
std::vector<T> arange(T start, T stop, T step = 1)
{
    std::vector<T> values {};
    for (T num = start; num < stop; num += step){
        values.emplace_back(num);
    }
    return values;
}

class Pair
{
private:
    int x_ {};
    int y_ {};
public:
    explicit Pair(const int x, const int y)
        : x_ {x}
        , y_ {y}
    {}
    explicit Pair(const char c1, const char c2)
        : x_ {c1 - '0'}
        , y_ {c2 - '0'}
    {}
    void print() const{
        std::cout << "Pair: (" << x_ << ", " << y_ << ")\n";
    }
};


int main()
{
    //std::string filename{"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day4_test.txt"};
    std::string filename{"/Users/reubenkouidri/Documents/Post-Uni/Cpp/Projects/Aoc22/day4_test.txt"};
    std::ifstream file {};

    file.open(filename);
    if (file.fail()){
        std::cout << "Failed to open file " << filename << '\n';
        return 1;
    }

    std::vector<Pair> v {};
    char c1, c2 {};
    std::string line {};

    while (std::getline(file, line))
    {
        std::stringstream ss;
        while (getline(file, line))
        line.erase(std::remove(line.begin(), line.end(), '-'), line.end());
        std::cout << line << '\n';
        ss << line;
        ss >> c1 >> c2;
        std::cout << "c1 " << c1 << ", c2 " << c2 << '\n';
        Pair p {c1, c2};
        p.print();
    }

    file.close();
    return 0;
}
