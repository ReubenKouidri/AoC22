#include <iostream>
#include <vector>
#include <fstream>

typedef std::vector<std::vector<int>> MatrixType;


[[maybe_unused]] void printMatrix(MatrixType& matrix) {
    for (const auto& r : matrix) {
        std::cout << "\n(";
        for (const auto i : r) {
            std::cout << i << ", ";
        }
        std::cout << ")\n";
    }
}

int leftScore(const MatrixType& m, const int row, const int col) {
    int score = 0;
    if (col == 0) return score;  // tree on left edge => left score = 0

    for (int q = col - 1; q > -1; q--) {
        score++;
        if (m[row][q] < m[row][col]) continue;
        else break;
    }

    return score;
}

int rightScore(const MatrixType& m, const int row, const int col) {
    int score = 0;
    if (col == m[0].size() - 1) return score;  // tree on right edge => right score = 0

    for (int q = col + 1; q < m[0].size(); q++) {
        score++;
        if (m[row][q] < m[row][col]) continue;
        else break;
    }

    return score;
}

int upScore(const MatrixType& m, const int row, const int col) {
    int score = 0;
    if (row == 0) return score;

    for (int p = row - 1; p > -1; p--) {
        score++;
        if (m[p][col] < m[row][col]) continue;
        else break;
    }

    return score;
}

int downScore(const MatrixType& m, const int row, const int col) {
    int score = 0;
    if (row == m.size()) return score;

    for (int p = row + 1; p < m.size(); p++) {
        score++;
        if (m[p][col] < m[row][col]) continue;
        else break;
    }

    return score;
}

[[clang::always_inline]] int scenicScore(const MatrixType& m, const int row, const int col) {
    return leftScore(m, row, col) * rightScore(m, row, col) * upScore(m, row, col) * downScore(m, row, col);
}

int main()
{
    std::ifstream stream {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day8/day8_data.txt"};
    std::string line {};
    int maxScore = 0;

    MatrixType matrix;

    while (std::getline(stream, line)){
        std::vector<int> row {};
        for (const auto i : line)
            row.emplace_back((i-'0'));  // '0'->0, '1'->1, etc.
        matrix.emplace_back(row);
    }

    const size_t rows = matrix.size();
    const size_t cols = matrix[0].size();

    for (size_t i = 0; i < rows; i++) {
        for (int j =0; j < cols; j++) {
            maxScore = std::max(scenicScore(matrix, i, j), maxScore);
        }
    }

    std::cout << maxScore << '\n';
    return 0;
};
