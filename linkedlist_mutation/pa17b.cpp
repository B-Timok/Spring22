/// @file List.hpp
/// @author Brandon Timok
/// @date 04/12/2022
/// @brief Program that constructs lists and includes many functions that
/// can mutate them.

#include "List.hpp"
#include <iostream>

int main() {

    List<int> integers{0, 1, 2, 3, 4, 5};
    if (integers.empty()) {
        std::cout << "is empty" << std::endl;
    }
    integers.erase(integers.begin());
    integers.insert(integers.end(), 6);
    
    std::cout << integers;
    std::cout << std::endl;

    return 0;
}