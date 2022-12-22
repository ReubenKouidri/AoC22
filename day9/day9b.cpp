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

typedef std::pair<int, int> gridPair;

struct Grid {
    std::vector<std::vector<int>> grid;
    std::vector<gridPair> pairs {};

    Grid(const size_t rows, const size_t cols, const gridPair& initPos) {
        for (size_t i = 0; i < rows; i++) {
            std::vector<int> row {};
            for (size_t j = 0; j < cols; j++) {
                row.emplace_back(0);
            }
            grid.emplace_back(row);
        }
        constexpr int numPairs = 10;
        for (int i = 0; i < numPairs; i++)
            this->pairs.emplace_back(initPos);
        this->grid[initPos.first][initPos.second] = 's';
    }

    [[nodiscard]] static INLINE bool adjacent(const gridPair& p1, const gridPair& p2) {
        if (std::abs(p1.first - p2.first) <= 1 && std::abs(p1.second - p2.second) <= 1)
            return true;
        return false;
    }

    void move(const char direction, const int magnitude) {
        switch (direction){
            case 'R':
                for (int i = 0; i < magnitude; i++) {
                    // head/tail (row, col)
                    pairs.front().second++;
                    for (int j = 0; j < pairs.size() - 1; j++) {
                        if (!adjacent(pairs[j], pairs[j+1])) {
                            pairs[j+1].second++;
                            if (pairs[j].first > pairs[j+1].first) pairs[j+1].first++;
                            if (pairs[j].first < pairs[j+1].first) pairs[j+1].first--;
                            grid[pairs.back().first][pairs.back().second] = 1;
                        }
                    }
                }
                return;
            case 'L':
                for (int i = 0; i < magnitude; i++) {
                    pairs.front().second--;
                    for (int j = 0; j < pairs.size() - 1; j++) {
                        if (!adjacent(pairs[j], pairs[j+1])) {
                            pairs[j+1].second--;
                            if (pairs[j].first > pairs[j+1].first) pairs[j+1].first++;
                            if (pairs[j].first < pairs[j+1].first) pairs[j+1].first--;
                            grid[pairs.back().first][pairs.back().second] = 1;
                        }
                    }
                }
                return;
            case 'U':
                for (int i = 0; i < magnitude; i++) {
                    pairs.front().first--;
                    for (int j = 0; j < pairs.size() - 1; j++) {
                        if (!adjacent(pairs[j], pairs[j+1])) {
                            pairs[j+1].first--;
                            if (pairs[j].second > pairs[j+1].second) pairs[j+1].second++;
                            if (pairs[j].second < pairs[j+1].second) pairs[j+1].second--;
                            grid[pairs.back().first][pairs.back().second] = 1;
                        }
                    }
                }
                return;
            case 'D':
                for (int i = 0; i < magnitude; i++) {
                    pairs.front().first++;
                    for (int j = 0; j < pairs.size() - 1; j++) {
                        if (!adjacent(pairs[j], pairs[j+1])) {
                            pairs[j+1].first++;
                            if (pairs[j].second > pairs[j+1].second) pairs[j+1].second++;
                            if (pairs[j].second < pairs[j+1].second) pairs[j+1].second--;
                            grid[pairs.back().first][pairs.back().second] = 1;
                        }
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
    std::pair<int, int> initPos {250, 250};  // (row, col)
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
