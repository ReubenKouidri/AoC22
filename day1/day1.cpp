#include <iostream>
#include <fstream>
#include <vector>


[[maybe_unused]] [[nodiscard]] auto printVect(const std::vector<int>& v) {
    for (const auto i : v)
        std::cout << i << '\n';
}


[[nodiscard]] auto sumElements(const std::vector<size_t>& vector, const int numElements) {
    size_t sum {};
    for (int i = 0; i < numElements; i++)
        sum += vector[i];
    return sum;
}


int main() {
    std::ifstream file {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day1/day1_data.txt"};
    size_t sum {};
    std::vector<size_t> elves {};
    std::string line {};

    while (std::getline(file, line) && file.good()) {
        if (line.empty()) {
            elves.emplace_back(sum);
            sum = 0;
        }
        else sum += std::stoul(line);
    }

    std::sort(elves.begin(), elves.end(), std::greater<>());

    std::cout << "\nThe third largest element is " << elves[2] << '\n';
    std::cout << "The second largest element is " << elves[1] << '\n';
    std::cout << "The largest element is " << elves[0] << '\n';

    std::cout << "Together, the top 3 elves carry " << sumElements(elves, 3) << " calories. " << '\n';
    return 0;
}
