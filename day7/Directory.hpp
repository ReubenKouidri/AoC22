
#ifndef AOC22_DIRECTORY_HPP
#define AOC22_DIRECTORY_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "File.hpp"


struct Directory {
    std::string name {};
    std::vector<std::unique_ptr<Directory>> dirs;
    std::vector<std::unique_ptr<File>> files;
    Directory* parent;
    size_t size {};

    explicit Directory(Directory* parent, std::string_view name)
            : name { name }
            , parent { parent }
    {}
    explicit Directory(std::string_view name)
            : name { name }
    {
        parent = this;
    }
};

#endif //AOC22_DIRECTORY_HPP
