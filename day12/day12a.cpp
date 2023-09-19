#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <queue>


// TODO:
//  - read in lines and get coordinates of 'S' and 'E'. ----------------------
//  - set 'S' == 'a' = 1. ----------------------
//  - set 'E' == 'z' = 26 ----------------------
//  - create grid ------------------
//  - create grid of visited locations
//  - create grid of possibilities
//  -
//  -

using Grid = std::vector<std::vector<int>>;
using Coordinate = std::pair<int, int>;


void printGrid(const Grid& grid) {
    for (const auto v : grid) {
        std::cout << '[';
        for (const auto i : v) {
            std::cout << i << ' ';
        }
        std::cout << " ]\n";
    }
}

int manhattanMetric(const int x1, const int y1, const int x2, const int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

struct Node {
    int x {};
    int y {};
    int g {};  // cost from start node
    int h {};  // estimated cost from end node
    int f {};  // g + h

    Node(const int x, const int y, const int g, const int h) : x(x), y(y), g(g), h(h), f(g + h) {}

    bool operator<(const Node& other) const {
        return f > other.f;
    }
};


std::vector<std::pair<int, int>> astar(const Grid& grid, Coordinate start, Coordinate end) {
    // path-finding algorithm
    // grid is know a priori so might be able to use a more efficient algorithm
    const std::uint32_t rows = grid.size();  // size_t is unsigned long
    const std::uint32_t cols = grid[0].size();
    std::vector<Coordinate> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    std::priority_queue<Node> openList {};  // priority automatically sorts values by largest on top
    std::vector<std::vector<bool>> closeList (rows, std::vector<bool>(cols, false));  // mark the nodes on the grid as visited or not

    Node startNode(start.first, start.second, 0, manhattanMetric(start.first, start.second, end.first, end.second));

}


int main () {
    std::string filename{"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day12/day12a_test.txt"};
    std::ifstream file {};

    file.open(filename);
    if (file.fail()) {
        std::cout << "Failed to open file " << filename << '\n';
        return 1;
    }

    std::string line {};
    std::vector<std::vector<int>> grid {};
    constexpr int ia {static_cast<int>('a')};
    constexpr int iNormalise {ia - 1};  // sets 'a' to 1 instead of 0
    Coordinate start {};
    Coordinate end {};
    int currentRow {};
    int currentCol {};

    while(std::getline(file, line)) {
        std::vector<int> row {};

        for (const char c : line) {
            int asciiValue = static_cast<int>(c) - iNormalise;
            if (c == 'S') {
                start.first = currentCol;
                start.second = currentRow;
                asciiValue = 1;
            }
            if (c == 'E') {
                end.first = currentCol;
                end.second = currentRow;
                asciiValue = 26;
            }
            row.emplace_back(asciiValue);
            currentCol++;
        }
        currentCol = 0;  // starting a new row so reset the column number to 0
        currentRow++;
        grid.emplace_back(row);
    }

    printGrid(grid);
    std::cout << "start (" << start.first << ", " << start.second << ")\n";
    std::cout << "end (" << end.first << ", " << end.second << ")\n";

    return 0;
};
