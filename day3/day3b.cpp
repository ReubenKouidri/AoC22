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


[[nodiscard]] size_t calcPriority(const std::vector<std::string>& vec) {
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


vsv_t SplitVector(const sv_t& vec, size_t n) {
    vsv_t outVec;
    std::size_t length = vec.size();
    std::size_t numSlices = length / n;
    size_t start = 0;
    size_t end = 0;

    for (size_t i = 0; i < numSlices; i++){
        end += n;
        outVec.emplace_back(sv_t(vec.begin() + start, vec.begin() + end));
        start = end;
    }

    return outVec;
}


int main() {
    std::ifstream file {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day3/day3_data.txt"};
    std::string line {};
    sv_t v {};

    while (std::getline(file, line) && !file.fail()) {
        std::stringstream ss;
        ss << line;
        v.emplace_back(line);
    }

    vsv_t triples = SplitVector(v, 3);
    size_t sumPriorities {};

    for (const auto& triple : triples)
        sumPriorities += calcPriority(triple);

    std::cout << "Priority: " << sumPriorities << '\n';
    return 0;
}
