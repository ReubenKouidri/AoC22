#include "MonkeyB.hpp"


auto setup(std::string_view filename) {
    std::ifstream file { filename };
    std::string line {};
    std::vector<std::unique_ptr<MonkeyB>> monkeys;

    while (std::getline(file, line)){
        if (line.substr(0,line.find(' ')) == "MonkeyB"){
            auto monkey {std::make_unique<MonkeyB>()};
            monkeys.emplace_back(std::move(monkey));
        }
        else if (line.substr(2, 8) == "Starting") {
            std::vector<long long> items;
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
    std::string filename {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day11/day11_test.txt" };
    auto monkeys = setup(filename);
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

    std::vector<long long> inspectedList;
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
