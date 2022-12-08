#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


int main()
{
    //std::string filename{"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day4_test.txt"};
    std::string filename{"/Users/reubenkouidri/Documents/Post-Uni/Cpp/Projects/Aoc22/day4_data.txt"};
    std::ifstream file {};

    file.open(filename);
    if (file.fail()){
        std::cout << "Failed to open file " << filename << '\n';
        return 1;
    }

    int c1, c2, c3, c4 {};
    std::string line {};
    int contains {};

    while (std::getline(file, line))
    {
        std::stringstream ss;
        std::replace(line.begin(), line.end(), '-', ' ');
        std::replace(line.begin(), line.end(), ',', ' ');
        ss << line;
        ss >> c1 >> c2 >> c3 >> c4;
        /* PART 1
        if (c3 >= c1 && c3 <= c2 && c4 >= c1 && c4 <= c2 || c1 >= c3 && c1 <= c4 && c2 >= c3 && c2 <= c4){
            contains++;
        }
        */
        /* PART 2
        if (c3 >= c1 && c3 <= c2 || c4 >= c1 && c4 <= c2 || c1 >= c3 && c1 <= c4 || c2 >= c3 && c2 <= c4){
            contains++;
        }
        */
    }
    std::cout << contains << '\n';
    file.close();
    return 0;
}
