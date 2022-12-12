#include <iostream>
#include <fstream>
#include <vector>


bool repeat(std::string& str)
{
    for (int i = 0; i < str.length(); i++){
        for (int j = 0; j < str.length(); j++){
            if (str[i] == str[i + j]){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::string filename {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day6/day6_test.txt"};
    std::ifstream file;

    file.open(filename);
    if (file.fail()){
        std::cout << "nope\n";
        return 1;
    }


    std::string s {};
    constexpr int filterLength { 4 };

    for (std::string line; std::getline(file, line); ){
        std::cout << line;
    }
    while (std::getline(file, s))
    {
        for (int i = 0; i < s.length() - filterLength; i++)
        {
            std::string ss = s.substr(i, filterLength);
            std::cout << ss << '\n';
            if (!repeat(ss))
            {
                std::cout << i + filterLength << '\n';
                break;
            }
        }
    }

    file.close();
    return 0;
};
