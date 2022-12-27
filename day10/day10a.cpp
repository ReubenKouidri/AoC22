#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>


class CPU {
    int currentCycle {};
    int registerVal { 1 };
    const std::set<int> triggerVals {20, 60, 100, 140, 180, 220};
    std::vector<int> signalStrengths;
public:
    void nextCycle() { currentCycle++; }
    void setRegister(const int val) { registerVal += val; }
    bool triggered() const { return triggerVals.contains(currentCycle); }
    void checkTrigger() {
        if (triggered())
            signalStrengths.emplace_back(registerVal * currentCycle);
    }
    const auto& getSignals() { return signalStrengths; }

};


int main() {
    std::ifstream file {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day10/day10_data.txt"};
    std::string line {};
    CPU cpu;

    while (std::getline(file, line)) {
        cpu.nextCycle();
        cpu.checkTrigger();
        if (line == "noop") continue;

        int val = std::stoi(line.substr(line.find(' '), std::string::npos));
        cpu.nextCycle();
        cpu.checkTrigger();
        cpu.setRegister(val);
    }

    int ans = 0;
    for (const auto i : cpu.getSignals())
        ans += i;
    std::cout << "Answer: " << ans << '\n';

    return 0;
}