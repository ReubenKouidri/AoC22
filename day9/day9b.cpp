#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>
#include <cassert>


#if __has_attribute(always_inline)
#define INLINE __attribute__((always_inline))
#else
#define INLINE
#endif

typedef std::pair<int, int> Pair_t;


struct Grid {
    std::vector<std::vector<int>> grid;
    std::vector<Pair_t> pairs {};
    std::vector<Pair_t> visitedLocs {};

    Grid(const size_t rows, const size_t cols, const Pair_t& initPos) {
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

    [[nodiscard]] static INLINE bool adjacent(const Pair_t& p1, const Pair_t& p2) {
        if ( std::abs(p1.first - p2.first) <= 1 && std::abs(p1.second - p2.second) <= 1 )
            return true;
        return false;
    }

    void movePair(const int pairIdx) {
        const Pair_t& p1 = pairs[pairIdx-1];
        Pair_t& p2 = pairs[pairIdx];
        int dc = p1.second - p2.second;  // dx
        int dr = p1.first - p2.first;  // dy
        std::cout << "dc " << dc << ", dr " << dr << '\n';
        if (dr == -2) {
            switch (dc) {
                case 2:
                    p2.first--;
                    p2.second++;
                    return;
                case 1:
                    p2.first--;
                    p2.second++;
                    return;
                case 0:
                    p2.first--;
                    return;
                case -1:
                    p2.first--;
                    p2.second--;
                    return;
                case -2:
                    p2.first--;
                    p2.second--;
                    return;
                default:
                    std::cout << "ERROR occurred in movePair!\n";
                    return;
            }
        }
        else if (dr == 2) {
            switch (dc) {
                case 2:
                    p2.first++;
                    p2.second++;
                    return;
                case 1:
                    p2.first++;
                    p2.second++;
                    return;
                case 0:
                    p2.first++;
                    return;
                case -1:
                    p2.first++;
                    p2.second--;
                    return;
                case -2:
                    p2.first++;
                    p2.second--;
                    return;
                default:
                    std::cout << "ERROR occurred in movePair!\n";
                    return;
            }
        }
        else if (dc == 2) {
            switch(dr) {
                case 1:
                    p2.first++;
                    p2.second++;
                    return;
                case 0:
                    p2.second++;
                    return;
                case -1:
                    p2.first--;
                    p2.second++;
                    return;
                default:
                    std::cout << "ERROR occurred in movePair!\n";
                    return;
            }
        }
        else if (dc == -2) {
            switch(dr) {
                case 1:
                    p2.first++;
                    p2.second--;
                    return;
                case 0:
                    p2.second--;
                    return;
                case -1:
                    p2.first--;
                    p2.second--;
                    return;
                default:
                    std::cout << "ERROR occurred in movePair!\n";
                    return;
            }
        }
        else std::cout << "Algo broke!\n";
    }

    void move(const char direction, const int magnitude) {
        std::cout << "direction " << direction << ", magnitude " << magnitude << '\n';
        switch (direction){
            case 'R':
                for (int i = 0; i < magnitude; i++) {
                    pairs.front().second++;  // first knot -> rhs
                    for (int j = 0; j < pairs.size() - 1; j++) {  // for every knot
                        if (!adjacent(pairs[j], pairs[j+1])) {  // check adjacent
                            movePair(j+1);
                            //pairs[j+1].second++;  // not adjacent at least due to col (since that's what we updated)
                            //if (pairs[j].first > pairs[j+1].first) pairs[j+1].first++; // diagonally down
                            //if (pairs[j].first < pairs[j+1].first) pairs[j+1].first--;  // diagonally up
                            //visitedLocs.emplace_back(pairs.back());
                            grid[pairs.back().first][pairs.back().second] = 1;
                        }
                        else break;
                    }
                }
                return;
            case 'L':
                for (int i = 0; i < magnitude; i++) {
                    pairs.front().second--;
                    for (int j = 0; j < pairs.size() - 1; j++) {
                        if (!adjacent(pairs[j], pairs[j+1])) {
                            //secondFollowFirst(pairs[j], pairs[j+1]);
                            //pairs[j+1].second--;  //TODO: BUG HERE!!
                            //if (pairs[j].first > pairs[j+1].first) pairs[j+1].first++;
                            //if (pairs[j].first < pairs[j+1].first) pairs[j+1].first--;
                            //visitedLocs.emplace_back(pairs.back());
                            movePair(j+1);
                            grid[pairs.back().first][pairs.back().second] = 1;
                        }
                        else break;
                    }
                }
                return;
            case 'U':
                for (int i = 0; i < magnitude; i++) {
                    pairs.front().first--;
                    for (int j = 0; j < pairs.size() - 1; j++) {
                        if (!adjacent(pairs[j], pairs[j+1])) {
                            //pairs[j+1].first--;
                            //if (pairs[j].second > pairs[j+1].second) pairs[j+1].second++;
                            //if (pairs[j].second < pairs[j+1].second) pairs[j+1].second--;
                            //visitedLocs.emplace_back(pairs.back());
                            movePair(j+1);
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
                            //pairs[j+1].first++;
                            //if (pairs[j].second > pairs[j+1].second) pairs[j+1].second++;
                            //if (pairs[j].second < pairs[j+1].second) pairs[j+1].second--;
                            //visitedLocs.emplace_back(pairs.back());
                            movePair(j+1);
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
        size_t score = 0;
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
        for (const auto& row : grid) {
            for (const auto i : row) {
                if (i == 0) std::cout << '.';
                else if (i == 's') std::cout << "s";
                else std::cout << '#';
            }
            std::cout << '\n';
        }
    }
};


int main()
{
    std::ifstream stream {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day9/day9b_test.txt"};
    std::string line {};
    char direction {};
    int magnitude {};
    // change if time allows as this is very rough!---
    std::pair<int, int> initPos {250, 250};  // (row, col)
    constexpr int rows {550};
    constexpr int cols {550};
    //------------------------------------------------
    auto g = std::make_unique<Grid> (rows, cols, initPos);
    while (std::getline(stream, line)) {
        std::stringstream ss;
        ss << line;
        ss >> direction >> magnitude;
        if (magnitude == 17) {
            g->move(direction, magnitude);
        }
        else g->move(direction, magnitude);

    }

    g->plot();
    std::cout << g->score() << '\n';
}
