#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>


#if __has_attribute(always_inline)
#define INLINE __attribute__((always_inline))
#else
#define INLINE
#endif


struct Grid {
    std::vector<std::vector<int>> grid {};
    std::pair<int, int> head {};  // (row, col)
    std::pair<int, int> tail {};

    Grid(const size_t rows, const size_t cols, const std::pair<int, int> initPos) {
        for (size_t i = 0; i < rows; i++) {
            std::vector<int> row {};
            for (size_t j = 0; j < cols; j++) {
                row.emplace_back(0);
            }
            grid.emplace_back(row);
        }
        //this->head = {initPos.first, initPos.second};
        this->head.first = initPos.first;
        this->tail.first = initPos.first;
        this->head.second = initPos.second;
        this->tail.second = initPos.second;
        this->grid[initPos.first][initPos.second] = 's';
    }

    [[nodiscard]] INLINE bool tailAdjacent() const {
        if (std::abs(head.first - tail.first) <= 1 && std::abs(head.second - tail.second) <= 1)
            return true;
        return false;
    }

    void move(const char direction, const int magnitude) {
        switch (direction){
            case 'R':
                for (int i = 0; i < magnitude; i++) {
                    // head/tail (row, col)
                    head.second++;
                    if (!tailAdjacent()) {
                        tail.second++;
                        if (head.first > tail.first) tail.first++;
                        if (head.first < tail.first) tail.first--;
                        grid[tail.first][tail.second] = 1;
                    }
                }
                return;
            case 'L':
                for (int i = 0; i < magnitude; i++) {
                    head.second--;
                    if (!tailAdjacent()) {
                        tail.second--;
                        if (head.first > tail.first) tail.first++;
                        if (head.first < tail.first) tail.first--;
                        grid[tail.first][tail.second] = 1;
                    }
                }
                return;
            case 'U':
                for (int i = 0; i < magnitude; i++) {
                    head.first--;
                    if (!tailAdjacent()) {
                        tail.first--;
                        if (head.second > tail.second) tail.second++;
                        if (head.second < tail.second) tail.second--;
                        grid[tail.first][tail.second] = 1;
                    }
                }
                return;
            case 'D':
                for (int i = 0; i < magnitude; i++) {
                    head.first++;
                    if (!tailAdjacent()) {
                        tail.first++;
                        if (head.second > tail.second) tail.second++;
                        if (head.second < tail.second) tail.second--;
                        grid[tail.first][tail.second] = 1;
                    }
                }
                return;
            default:
                std::cout << "\nSWITCH FAILED!\n";
                return;
        }
    }

    [[nodiscard]] size_t score() const {
        size_t score = 1;
        for (const auto& v : grid) {
            for (const auto i : v) {
                if (i == 1) {
                    score++;
                }
            }
        }
        return score;
    }

    void plot() {
        for (const auto& i : grid) {
            for (const auto j : i) {
                if (j == 0) std::cout << '.';
                else if (j == 's') std::cout << "s";
                else std::cout << '#';
            }
            std::cout << '\n';
        }
    }
};


int main()
{
    std::ifstream stream {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day9/day9_data.txt"};
    std::string line {};
    char direction {};
    int magnitude {};
    // change if time allows as this is very rough!---
    std::pair<int, int> initPos {300, 300};  // (row, col)
    constexpr int rows {600};
    constexpr int cols {600};
    //------------------------------------------------
    auto g = std::make_unique<Grid> (rows, cols, initPos);

    while(std::getline(stream, line)) {
        std::stringstream ss;
        ss << line;
        ss >> direction >> magnitude;
        g->move(direction, magnitude);
    }
    g->plot();
    std::cout << g->score() << '\n';
}