#include "MonkeyA.hpp"


void MonkeyA::inspectItems(){
    for (auto& item : items)
        inspectItem(item);
}

void MonkeyA::inspectItem(size_t& item) {
    itemsInspected++;
    switch(operation) {
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

void MonkeyA::makeTurn(std::vector<std::unique_ptr<MonkeyA>>& monkeys) {
    if (!items.empty()) {
        inspectItems();
        std::vector<size_t> trueVec;
        std::vector<size_t> falseVec;
        for (const auto item: items) {
            (item % divisibleBy == 0 && item >= divisibleBy) ?
            trueVec.emplace_back(item) : falseVec.emplace_back(item);
        }
        monkeys[trueMonkey]->items.insert(monkeys[trueMonkey]->items.end(), trueVec.begin(), trueVec.end());
        monkeys[falseMonkey]->items.insert(monkeys[falseMonkey]->items.end(), falseVec.begin(), falseVec.end());
        items.erase(items.begin(), items.end());
    }
}

void MonkeyA::printItems() const {
    std::cout << " Items: ";
    for (const auto i : items) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}
