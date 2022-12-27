#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


struct CRT {  // cathode ray tube
private:
    size_t rayPos {};
public:
    struct Screen {
        static constexpr size_t width = 40;
        static constexpr char trueChar = '#';
        static constexpr char falseChar = '.';
        std::vector<char> pixels;
    } screen;

    struct CPU {
        size_t currentCycle {};
        size_t spriteCentre { 1 };
        void updateRegister(const size_t val) { spriteCentre += val; }
    } cpu;

    void addPixel() {
        std::cout << "Sprite pos : (" << cpu.spriteCentre-1 << ", " << cpu.spriteCentre << ", " << cpu.spriteCentre+1 << ")\n";
        std::cout << "adding pixel at ray pos " << rayPos << '\n';
        size_t spritePos[3] = {cpu.spriteCentre - 1, cpu.spriteCentre, cpu.spriteCentre + 1};
        if (std::find(std::begin(spritePos), std::end(spritePos), rayPos) != std::end(spritePos))
            screen.pixels.emplace_back(CRT::Screen::trueChar);
        else
            screen.pixels.emplace_back(CRT::Screen::falseChar);
    }
    void drawScreen() const {
        for (size_t pixelNum = 0; pixelNum < screen.pixels.size(); pixelNum++) {
            if (pixelNum % CRT::Screen::width == 0) std::cout << '\n';
            std::cout << screen.pixels[pixelNum];
        }
    }
    void nextCycle() {
        cpu.currentCycle++;  // start next cpu cycle
        addPixel();  // draw pixel for current cycle
        rayPos++;
        if (rayPos >= 40) rayPos -= 40;
    }
};


int main() {
    std::ifstream file {"/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day10/day10_data.txt"};
    std::string line {};
    CRT crt;

    while (std::getline(file, line)) {
        crt.nextCycle();
        if (line == "noop") continue;

        size_t val = std::stoul(line.substr(line.find(' '), std::string::npos));
        crt.nextCycle();
        crt.cpu.updateRegister(val);
    }
    crt.drawScreen();

    return 0;
}
