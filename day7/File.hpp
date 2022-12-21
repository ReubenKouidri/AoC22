
#ifndef AOC22_FILE_HPP
#define AOC22_FILE_HPP

#include <iostream>
#include <string>


struct File {
    std::string name {};
    std::size_t size {};

    explicit File(std::string_view name, const size_t size)
            : name{ name }
            , size{ size }
    {}
};


#endif //AOC22_FILE_HPP
