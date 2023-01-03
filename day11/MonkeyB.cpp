#include "MonkeyB.hpp"


void MonkeyB::inspectItems(){
    for (auto& item : items)
        inspectItem(item);
}

void MonkeyB::inspectItem(long long& item) {
    itemsInspected++;
    switch(operation) {
        case '+':
            item = std::floor((item + magnitude));
            break;
        case '*':
            item = std::floor((item * magnitude));
            break;
        case 's':
            item = std::floor(std::pow(item, 2));
            break;
        default:
            std::cout << "BUG IN OPERATION";
            break;
    }
}

void MonkeyB::makeTurn(std::vector<std::unique_ptr<MonkeyB>>& monkeys) {
    if (!items.empty()) {
        inspectItems();
        std::vector<long long> trueVec;
        std::vector<long long> falseVec;
        for (const auto item: items) {
            (item % divisibleBy == 0 && item >= divisibleBy) ?
            trueVec.emplace_back(item) : falseVec.emplace_back(item);
        }
        monkeys[trueMonkey]->items.insert(monkeys[trueMonkey]->items.end(), trueVec.begin(), trueVec.end());
        monkeys[falseMonkey]->items.insert(monkeys[falseMonkey]->items.end(), falseVec.begin(), falseVec.end());
        items.erase(items.begin(), items.end());
    }
}

void MonkeyB::printItems() const {
    std::cout << " Items: ";
    for (const auto i : items) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}
