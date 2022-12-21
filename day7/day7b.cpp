#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


struct File {
    std::string name {};
    std::size_t size {};
};

struct Directory {
    std::string name {};
    std::vector<std::unique_ptr<Directory>> dirs;
    std::vector<std::unique_ptr<File>> files;
    Directory* parent;
    std::size_t size {};
};


void traverse(Directory* mainDir, int level) {
    for (int i = 0; i < level; i++)
        std::cout << "  ";
    std::cout << "- " << mainDir->name << "(dir)\n";
    for (const auto& dir : mainDir->dirs)
        traverse(dir.get(), level + 1);
    for (const auto& file : mainDir->files){
        for (int j = 0; j < level; j++)
            std::cout << "  ";
        std::cout << "- " << file->name << "(file, size=" << file->size << ")\n";
    }
}

size_t updateSize(Directory* topDir) {
    for (const auto &dir: topDir->dirs)
        topDir->size += updateSize(dir.get());
    for (const auto& file : topDir->files)
        topDir->size += file->size;

    return topDir->size;
}


size_t findSmallestRequiredDir(Directory* mainDir, size_t requiredMin){

    size_t min = mainDir->size;  // initial min

    for (const auto& dir : mainDir->dirs) {
        if (dir->size >= requiredMin) {
            const auto deeperMin = findSmallestRequiredDir(dir.get(), requiredMin);
            min = std::min(min, deeperMin);
        }
    }

    return min;
}


int main(int argc, char* argv[]) {
    std::string fileName = "/Users/juliettekouidri/Documents/Reuben/Projects/Cpp/AoC22/day7/day7_data.txt";
    if (argc > 1) {
        fileName = argv[1];
    }

    std::string line {};
    std::fstream file(fileName);

    auto topDir { std::make_unique<Directory>() };
    topDir->name = '/';
    topDir->parent = topDir.get();  // returns the 'stored pointer' pointing to the object managed by unique_ptr
    auto cd { topDir.get() };
    bool skip { false };
    constexpr std::size_t EOC = 5;  // end of cmd

    while(skip || std::getline(file, line)) {
        skip = false;
        if (line[0] == '$'){
            // TODO: BUG where index goes beyond line length
            const auto idx = line.find(' ', 2);  // find where ' ' occurs beyond index 2
            const auto cmd = line.substr(2, idx - 2);
            if (cmd == "cd") {
                const auto dest = line.substr(EOC, std::string::npos);
                if (dest == "..") cd = cd->parent;
                else if (dest == "/") cd = topDir.get();
                else {
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
                        cd -> dirs.emplace_back();
                        cd -> dirs.back() -> name = dest;
                        cd->dirs.back()->parent = cd;
                        cd = cd->dirs.back().get();
                        std::cout << "Now, cd = " << cd->name << '\n';
                    }
                }
            }
            else if (cmd == "ls") {
                while (std::getline(file, line)) {
                    if (line.substr(0, 3) == "dir") {  // [x1, x2)
                        const auto dirName = line.substr(4, std::string::npos);
                        // TODO: change 'found' to 'alreadyExists' or something more descriptive
                        bool found = false;
                        for (const auto& dir : cd -> dirs) {
                            if (dir->name == "dirName")
                                found = true;
                        }
                        if (!found) {
                            std::cout << "Adding new dir: " << dirName << '\n';
                            cd->dirs.emplace_back(std::make_unique<Directory>());
                            cd->dirs.back()->parent = cd;
                            cd->dirs.back()->name = dirName;
                        }
                    }
                    else if (line[0] != '$') {  // add files
                        const auto sepPos = line.find(' ');
                        const auto fileSize = std::stoul(line.substr(0, sepPos));
                        const auto name = line.substr(sepPos + 1, std::string::npos);
                        std::cout << "Adding file: " << name << " with size " << fileSize << '\n';
                        cd->files.emplace_back(std::make_unique<File>());
                        cd->files.back()->size = fileSize;
                        cd->files.back()->name = name;
                    }
                    else {
                        std::cout << "else clause\n";
                        skip = true;
                        break;  // end while
                    }
                }
            }
        }
    }
    traverse(topDir.get(), 0);
    updateSize(topDir.get());
    constexpr size_t diskSpace { 70000000 };
    constexpr size_t requiredSpace { 30000000 };
    const size_t freeSpace = diskSpace - topDir->size;
    const size_t minDeleteSize = requiredSpace - freeSpace;
    std::cout << topDir -> size << '\n';
    std::cout << freeSpace << '\n';
    std::cout << minDeleteSize << '\n';
    std::cout << "Min = " << findSmallestRequiredDir(topDir.get(), minDeleteSize) << '\n';

    return 0;
};
