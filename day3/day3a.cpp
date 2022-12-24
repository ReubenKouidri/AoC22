//
// Created by Juliette Kouidri on 05/12/2022.
//

#include <vector>
#include <iostream>


[[nodiscard]] [[nodiscard]] int convertCharToRange(unsigned char c) // converts to [1, 52]
{
    // map chars to desired range:
    // [a, z; A, Z] = [1, 26; 27, 52]
    // from
    // [A, Z; a, z] = [65, 90; 97, 122]
    int p { (int)c };
    if ( p >= 'a'){
        return p - 96;  // map [a, z] -> [1, 26]
    }
    return p - 38;  // map [A, Z] -> [27, 52]
}


[[maybe_unused]] [[nodiscard]] unsigned char findSharedChar(const std::string& s1, const std::string& s2)
{
    int match[128] {};  //128 ascii values
    unsigned char common {};
    for (unsigned char c : s1)
        match[(int)c]++;

    for (unsigned char c : s2)
    {
        if (match[(int)c] != 0)
        {
            std::cout << c << " is a common char with priority " << convertCharToRange(c) << '\n';
            common = c;
            break;
        }
    }
    return common;
}

[[maybe_unused]] [[nodiscard]] int calcPriority(const std::vector<std::string>& vec)
{
    constexpr static int numChars { 52 };
    int priority {};
    bool primaryArray [numChars] {};

    std::memset(primaryArray, true, sizeof(primaryArray));

    for (const auto & s : vec)
    {
        bool secondArray [numChars] {false};

        for (const auto c : s){
            if (primaryArray[convertCharToRange(c) - 1]){
                secondArray[convertCharToRange(c) - 1] = true;
            }
        }
        std::memcpy(primaryArray, secondArray, numChars);
    }

    for (int i = 0; i < numChars; i++) {
        if (primaryArray[i]){
            std::cout << i + 1 << '\n';
            priority = i + 1;
        }
    }
    return priority;
}


VVS_t SplitVector(const std::vector<std::string>& vec, int n)
{
    std::vector<std::vector<std::string>> outVec;

    std::size_t length = vec.size();
    std::size_t numSlices = length / n;
    int start = 0;
    int end = 0;

    for (int i = 0; i < numSlices; i++){
        end += n;
        outVec.emplace_back(std::vector<std::string>(vec.begin() + start, vec.begin() + end));
        start = end;
    }

    return outVec;
}

/*
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
    */

    /* // part 1----------------------------------------------
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
    file.close();
    return 0;
}
    */
