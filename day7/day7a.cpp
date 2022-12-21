#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include "Directory.hpp"  // includes vector and File.hpp


void traverse(Directory* dir, int depth) {  // depth is used for illustration purposes only
    for (int i = 0; i < depth; i++)
        std::cout << "  ";
    std::cout << "- " << dir->name << "(dir)\n";
    for (const auto& d : dir->dirs)
        traverse(d.get(), depth + 1);
    for (const auto& file : dir->files) {
        for (int j = 0; j < depth; j++)
            std::cout << "  ";
        std::cout << "- " << file->name << "(file, size=" << file->size << ")\n";
    }
}

size_t calcSizes(Directory* dir) {
    for (const auto &d: dir->dirs)
        dir->size += calcSizes(d.get());
    for (const auto& file : dir->files)
        dir->size += file->size;

    return dir->size;
}

size_t totalSizeLteThreshold(Directory* dir, size_t threshold) {
    size_t sum = 0;
    for (const auto& d : dir -> dirs) {
        if (d->size <= threshold) {
            sum += d->size;
        }
        const auto insideThatDir = totalSizeLteThreshold(d.get(), threshold);
        sum += insideThatDir;
    }

    return sum;
}


int main() {
    std::string fileName = "/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day7/day7_data.txt";

    std::string line {};
    std::fstream file(fileName);

    auto outerMostDir = std::make_unique<Directory>("/");
    auto cd = outerMostDir.get();
    bool skip = false;
    constexpr size_t EOC = 5;  // end of cmd

    while(skip || std::getline(file, line)) {
        skip = false;
        if (line[0] == '$'){
            // TODO: BUG where index goes beyond line length
            const auto idx = line.find(' ', 2);  // find where ' ' occurs beyond index 2 
            const auto cmd = line.substr(2, idx - 2);
            if (cmd == "cd") {
                const auto dest = line.substr(EOC, std::string::npos);
                if (dest == "..") cd = cd->parent;
                else if (dest == "/") cd = outerMostDir.get();
                else {  // change directory
                    bool found = false;
                    for (const auto& dir : cd->dirs) {
                        if (dir->name == dest) {
                            found = true;
                            cd = dir.get();  // change cd to the dest dir indicated by the '$ cd X' cmd
                            std::cout << "cd = " << cd->name << '\n';
                            break;
                        }
                    }
                    if (!found) {
                        std::cout << "Adding dir: " << dest << '\n';
                        Directory newDir = Directory(cd, dest);
                        cd -> dirs.emplace_back(std::make_unique<Directory>(cd, dest));
                        cd = cd->dirs.back().get();
                        std::cout << "Now, cd = " << cd->name << '\n';
                    }
                }
            }
            else if (cmd == "ls") {
                while (std::getline(file, line)) {
                    if (line.substr(0, 3) == "dir") {  // [x1, x2)
                        const auto dirName = line.substr(4, std::string::npos);
                        bool exists = false;  // assume does not exist
                        for (const auto& dir : cd -> dirs) {
                            if (dir->name == "dirName") exists = true;  // and do nothing
                        }
                        if (!exists)
                            cd->dirs.emplace_back(std::make_unique<Directory>(cd, dirName));
                    }
                    else if (line[0] != '$') {  // add files
                        const auto sepPos = line.find(' ');
                        const auto fileSize = std::stoul(line.substr(0, sepPos));
                        const auto name = line.substr(sepPos + 1, std::string::npos);
                        std::cout << "Adding file: " << name << " with size " << fileSize << '\n';
                        cd->files.emplace_back(std::make_unique<File>(name, fileSize));
                    }
                    else {
                        skip = true;
                        break;
                    }
                }
            }
        }
    }
    traverse(outerMostDir.get(), 0);
    calcSizes(outerMostDir.get());
    constexpr size_t sizeThreshold { 100000 };
    std::cout << totalSizeLteThreshold(outerMostDir.get(), sizeThreshold) << '\n';
    return 0;
};
