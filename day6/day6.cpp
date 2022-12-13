#include <iostream>
#include <fstream>


bool isUnique(const int arr [], size_t size){
    for (int i = 0; i < size; i++){
        if (arr[i] > 1)
            return false;
    }
    return true;
}

int main()
{
    std::ifstream stream {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day6/day6_data.txt"};
    std::string s {};
    constexpr int filterLength { 4 };


    while (std::getline(stream, s)){
        for (int i = 0; i < s.length() - filterLength; i++) {
            int match[128] {};  //128 ascii values
            std::string ss = s.substr(i, filterLength);
            for (const auto c: ss) {
                match[c]++;
            }
            if (isUnique(match, sizeof(match)/sizeof(match[0]))) {
                std::cout << i + filterLength << '\n';
                break;
            }
        }
    }

    return 0;
};
