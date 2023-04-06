/// @file pa14.cpp
/// @author Brandon Timok 
/// @date 03/14/2022
/// @brief Program that asks you for lottery numbers.
/// the more you win!

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Container.hpp"

int main() {
    Container<int> lottery;
    Container<int> user {0, 0, 0, 0, 0};

    int matching_num = 0;
    int prize_money = 0;
    std::string option;

    do {

    srand(std::time(nullptr));

    while (lottery.size() < 5) {
        int random_num = std::rand() % 10;
        
        if (std::find(lottery.begin(), lottery.end(), random_num) == lottery.end()) {
            lottery.push_back(random_num);
        }
    }
    
    // std::cout << lottery << std::endl;
    std::cout << "Enter five unique lottery digits between 0 and 10: ";
    for (auto i = 0; i < 5; ++i) {
        std::cin >> user.at(i);
    }

    for (auto i = 0; i < 5; ++i) {
        if (std::find(lottery.begin(), lottery.end(), user.at(i)) != lottery.end()) {
            matching_num += 1;
        }
    }

    if (std::equal(user.begin(), user.end(), lottery.begin())) {
        prize_money = 10000;
    } else if (matching_num == 5) {
        prize_money = 3000;
    } else {
        prize_money = matching_num * 125;
    }

    std::cout << '\n';
    std::cout << "Congratulations! You matched " << matching_num << " digits!" << '\n';
    std::cout << "Your prize is $" << prize_money << '\n';
    std::cout << '\n';
    std::cout << "Winning numbers: " << lottery << std::endl;
    std::cout << "Your picks:      " << user << std::endl;
    std::cout << '\n';
    std::cout << "Play again (yes/no)? ";
    std::cin >> option;
    std::cout << '\n';

    matching_num = 0;

    } while (option == "yes");

    std::cout << "Good luck!" << std::endl;

    return 0;
}
