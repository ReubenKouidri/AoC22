#ifndef AOC22_MONKEYB_HPP
#define AOC22_MONKEYB_HPP


#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <cmath>


class MonkeyB {
    char operation {};
    size_t magnitude {};
    size_t itemsInspected {};
    size_t trueMonkey {};
    size_t falseMonkey {};
    size_t divisibleBy {};
    std::vector<long long> items {};
public:
    MonkeyB() = default;
    explicit MonkeyB(std::vector<long long> vec) : items {std::move(vec )} {}
    [[nodiscard]] size_t getNumInspected() const { return itemsInspected; };
    void inspectItems();
    void inspectItem(long long& item);
    void makeTurn(std::vector<std::unique_ptr<MonkeyB>>& monkeys);
    void initItems(std::vector<long long> newItems) { items = std::move(newItems); };
    void setTrueTarget(const size_t otherId) { trueMonkey = otherId; }
    void setFalseTarget(const size_t otherId) { falseMonkey = otherId; }
    void setOp(const char c) { operation = c; }
    void setMag(const size_t i) { magnitude = i; }
    void setDivisibleBy(const size_t d) { divisibleBy = d; }
    void printItems() const;
};


#endif //AOC22_MONKEYB_HPP
