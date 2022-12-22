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

bool visibleAlongRow(const MatrixType& matrix, const int element, const int row, const int col) {
    bool lhs = true;
    bool rhs = true;

    //lhs
    for (int q = col - 1; q != -1; q--) {
        if (matrix[row][q] >= element)
            lhs = false;
    }
    // compare along row to rhs
    for (size_t q = col + 1; q < matrix[0].size(); q++) {
        if (matrix[row][q] >= element)
            rhs = false;
    }
    return (lhs || rhs);
}

bool visibleInCol(const MatrixType &matrix, const int element, const int row, const int col) {
    bool up = true;
    bool down = true;

    // up
    for (int p = row - 1; p > -1; p--) {
        if (matrix[p][col] >= element)
            up = false;
    }
    // down
    for (int p = row + 1; p < matrix.size(); p++) {
        if (matrix[p][col] >= element) {
            down = false;
        }
    }
    return (up || down);
}


bool visible(const MatrixType& matrix, const int row, const int col) {
    const int element = matrix[row][col];
    // perimeter
    if (row == 0 || col == 0)
        return true;

    return (visibleAlongRow(matrix, element, row, col) || visibleInCol(matrix, element, row, col));
}

int main()
{
    std::ifstream stream {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day8/day8_data.txt"};
    std::string line {};
    size_t count = 0;

    MatrixType matrix;

    while (std::getline(stream, line)){
        std::vector<int> row {};
        for (const auto i : line)
            row.emplace_back((i-'0'));  // i-'0' converts '0'->0, '1'->1, etc.
        matrix.emplace_back(row);
    }

    const size_t rows = matrix.size();
    const size_t cols = matrix[0].size();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (visible(matrix, row, col))
                count++;
        }
    }
    std::cout << count << '\n';
    return 0;
};
