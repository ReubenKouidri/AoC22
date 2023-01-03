#ifndef AOC22_MONKEYA_HPP
#define AOC22_MONKEYA_HPP

#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <cmath>


class MonkeyA {
    char operation {};
    size_t magnitude {};
    size_t itemsInspected {};
    size_t trueMonkey {};
    size_t falseMonkey {};
    size_t divisibleBy {};
    std::vector<size_t> items {};
public:
    MonkeyA() = default;
    explicit MonkeyA(std::vector<size_t> vec) : items {std::move(vec )} {}
    [[nodiscard]] size_t getNumInspected() const { return itemsInspected; };
    void inspectItems();
    void inspectItem(size_t& item);
    void makeTurn(std::vector<std::unique_ptr<MonkeyA>>& monkeys);
    void initItems(std::vector<size_t> newItems) { items = std::move(newItems); };
    void setTrueTarget(const size_t otherId) { trueMonkey = otherId; }
    void setFalseTarget(const size_t otherId) { falseMonkey = otherId; }
    void setOp(const char c) { operation = c; }
    void setMag(const size_t i) { magnitude = i; }
    void setDivisibleBy(const size_t d) { divisibleBy = d; }
    void printItems() const;
};


#endif //AOC22_MONKEYA_HPP
