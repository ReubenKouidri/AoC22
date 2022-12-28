#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>


class Monkey {
    int id {};
    int magnitude {};
    int itemsInspected {};
    char operation {};
    int trueMonkey {};  // monkey that item gets thrown to if true
    int falseMonkey {};  // monkey that item gets thrown to if false
    std::vector<int> items {};
public:
    explicit Monkey(std::vector<int>  vec) : items {std::move( vec )}
    {}
    explicit Monkey(const int num) : id {num}
    {}
    void test(const int worryLevel) {
        // e.g. divisible by 23? true : false
    }
    void initItems(const std::vector<int>& newItems) { items = newItems; }

    void throwItem(Monkey* other) {
        if (!items.empty()) {
            other->items.emplace_back(items[0]);
            items.erase(items.begin());
        }
        else {
            std::cout << "Monkey " << id << " is not holding any items!\n";
        }
    }
    [[nodiscard]] int inspectItem(const int num, const int worryLevel) const {
        int result {};
        switch (operation) {
            case '+':
                result = num + worryLevel;
                break;
            case '*':
                result = num * worryLevel;
                break;
            default:
                std::cout << "BUG IN OPERATION";
                break;
        }
        return result;
    }
    void setTrueTarget(const int otherId) { trueMonkey = otherId; }
    void setFalseTarget(const int otherId) { falseMonkey = otherId; }
    void setOp(const char c) { operation = c; }
    void setMag(const int i) { magnitude = i; }
};


auto setup() {
    std::ifstream file {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day11/day11_test.txt"};
    std::string line {};
    std::vector<std::unique_ptr<Monkey>> monkeys;

    while (std::getline(file, line)){
        if (line.substr(0,line.find(' ')) == "Monkey"){
            auto monkey {std::make_unique<Monkey> (std::stoi(line.substr(line.find(' ') + 1, 1)))};
            monkeys.emplace_back(std::move(monkey));
        }
        else if (line.substr(2, 8) == "Starting") {
            std::vector<int> items;
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
                break;
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
    /* for 20 rounds do:
     *   m inspects item
     *   new = operation // 3, e.g. new = (old * old) // 3 (FLOOR)
     *   if test true: throw item to m2, else throw item to m3
     *   m inspects next item...
     *
     *   repeat
     *
    */

    return 0;
}