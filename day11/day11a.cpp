#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <cmath>


class Monkey {
    size_t magnitude {};
    size_t itemsInspected {};
    char operation {};
    size_t trueMonkey {};  // monkey that item gets thrown to if true
    size_t falseMonkey {};  // monkey that item gets thrown to if false
    size_t divisibleBy {};
    std::vector<size_t> items {};
public:
    explicit Monkey(std::vector<size_t>  vec) : items {std::move( vec )}
    {}
    Monkey() = default;
    void initItems(const std::vector<size_t>& newItems) { items = newItems; }

    void throwItem(Monkey* other) {
        other->items.emplace_back(items[0]);  // throw first item in list
        items.erase(items.begin());  // remove it
    }
    void inspectItems() {
        for (auto& item : items)
            inspectItem(item);
    }
    void inspectItem(size_t& item) {
        itemsInspected++;
        switch (operation) {
            case '+':
                item = std::floor((item + magnitude) / 3);
                break;
            case '*':
                item = std::floor((item * magnitude) / 3);
                break;
            case 's':
                item = std::floor(std::pow(item, 2) / 3);
                break;
            default:
                std::cout << "BUG IN OPERATION";
                break;
        }
    }
    void makeTurn(std::vector<std::unique_ptr<Monkey>>& monkeys) {
        if (!items.empty()) {
            inspectItems();
            for (const auto item : items) {
                item % divisibleBy == 0 ?
                throwItem(monkeys[trueMonkey].get()) : throwItem(monkeys[falseMonkey].get());
            }
        }
    }
    [[nodiscard]] size_t getNumInspected() const { return itemsInspected; }
    void setTrueTarget(const size_t otherId) { trueMonkey = otherId; }
    void setFalseTarget(const size_t otherId) { falseMonkey = otherId; }
    void setOp(const char c) { operation = c; }
    void setMag(const size_t i) { magnitude = i; }
    void setDivisibleBy(const size_t d) { divisibleBy = d; }
    void printItems() const {
        std::cout << " Items: ";
        for (const auto i : items) {
            std::cout << i << " ";
        }
        std::cout << '\n';
    }
};

auto setup() {
    std::ifstream file {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day11/day11_test.txt"};
    std::string line {};
    std::vector<std::unique_ptr<Monkey>> monkeys;

    while (std::getline(file, line)){
        if (line.substr(0,line.find(' ')) == "Monkey"){
            auto monkey {std::make_unique<Monkey>()};
            monkeys.emplace_back(std::move(monkey));
        }
        else if (line.substr(2, 8) == "Starting") {
            std::vector<size_t> items;
            std::stringstream ss;
            const auto subs = line.substr(line.find(": ") + 2);

            ss << subs;
            int n;
            std::string word {};
            while (!ss.eof()) {
                ss >> word;
                if (std::stringstream(word) >> n) { items.emplace_back(n); }
            }
            monkeys.back()->initItems(items);
        }

        else if (line.substr(2,9) == "Operation") {
            const auto substring = line.substr(line.find("old") + 4, std::string::npos); // e.g. "* old"
            std::stringstream ss;
            ss << substring;

            if (substring.find("old") != std::string::npos) {  // if "old" found => old * old
                monkeys.back()->setOp('s');
                continue;
            }

            char op{substring[0]};
            monkeys.back()->setOp(op);
            int n{};
            std::string word{};
            while (!ss.eof()) {
                ss >> word;
                if (std::stringstream(word) >> n) {
                    monkeys.back()->setMag(n);
                    break;
                }
            }
        }
        else if (line.substr(2, 4) == "Test") {
            int lineNum = 0;
            int divisBy = std::stoi(line.substr(line.find('y') + 2));
            monkeys.back()->setDivisibleBy(divisBy);
            while (std::getline(file, line) && lineNum < 2) {
                const auto subs = line.substr(line.find('y') + 2);
                int dest = std::stoi(subs);
                if (lineNum == 0) {
                    monkeys.back()->setTrueTarget(dest);
                }
                if (lineNum == 1) {
                    monkeys.back()->setFalseTarget(dest);
                }
                lineNum++;
            }
        }
        else continue;
    }

    return monkeys;
}

int main() {
    auto monkeys = setup();
    constexpr int rounds = 20;

    for (int round = 0; round < rounds; round++) {
        std::cout << "Start of round " << round << '\n';
        for (auto& monkey : monkeys) {
            monkey->makeTurn(monkeys);
        }
        for (auto& monkey : monkeys) {
            monkey->printItems();
        }
    }

    std::vector<size_t> inspectedList;
    for (const auto& monkey : monkeys) {
        inspectedList.emplace_back(monkey->getNumInspected());
    }
    std::sort(inspectedList.begin(), inspectedList.end(), std::greater<>());
    for (const auto i : inspectedList) {
        std::cout << i << " \n";
    }
    std::cout << inspectedList[0] * inspectedList[1] << '\n';

    return 0;
}










































