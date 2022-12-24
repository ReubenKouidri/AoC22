#include "day3_imports.hpp"


[[nodiscard]] size_t convertCharToRange(unsigned char c) { // converts to [1, 52]
    // map chars to desired range:
    // [a, z; A, Z] = [1, 26; 27, 52]
    // from
    // [A, Z; a, z] = [65, 90; 97, 122]
    size_t p { (size_t)c };
    if ( p >= 'a'){
        return p - 96;  // map [a, z] -> [1, 26]
    }
    return p - 38;  // map [A, Z] -> [27, 52]
}


[[nodiscard]] unsigned char findSharedChar(const std::string& s1, const std::string& s2) {
    size_t match[128] {};  //128 ascii values
    unsigned char common {};
    for (const unsigned char c : s1)
        match[(size_t)c]++;

    for (const unsigned char c : s2) {
        if (match[(size_t)c] != 0) {
            std::cout << c << " is a common char with priority " << convertCharToRange(c) << '\n';
            common = c;
            break;
        }
    }
    return common;
}


[[nodiscard]] size_t calcPriority(const sv_t& vec) {
    constexpr static size_t numChars { 52 };
    size_t priority {};
    bool primaryArray [numChars] {};

    std::memset(primaryArray, true, sizeof(primaryArray));

    for (const auto& s : vec) {
        bool secondArray [numChars] {false};

        for (const auto c : s) {
            if (primaryArray[convertCharToRange(c) - 1])
                secondArray[convertCharToRange(c) - 1] = true;
        }

        std::memcpy(primaryArray, secondArray, numChars);
    }

    for (size_t i = 0; i < numChars; i++) {
        if (primaryArray[i]){
            std::cout << i + 1 << '\n';
            priority = i + 1;
        }
    }
    return priority;
}


int main() {
    std::ifstream file {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day3/day3_data.txt"};
    std::string line {};
    sv_t v {};

    size_t sum {};
    while (std::getline(file, line)) {
        std::stringstream ss;
        ss << line;  // e.g. "AjfuHndhTL"
        std::string firstHalf = line.substr(0, line.length() / 2);  // assumes even length strings
        std::string secondHalf = line.substr(line.length() / 2);
        unsigned char shared = findSharedChar(firstHalf, secondHalf);
        sum += convertCharToRange(shared);
    }

    std::cout << sum << '\n';
    file.close();
    return 0;
}
