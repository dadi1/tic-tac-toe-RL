#include "../include/HumanAgent.hpp"

#include <iostream>
#include <limits>
#include <algorithm>

int HumanAgent::choose_action(const std::string& state, const std::vector<int>& legal_moves) {

    print_board(state); // prints board for better vizualization for human player.
    
    std::cout << "You're the X player, make yor move." << std::endl;

    int position;

    while(true) {

        // Looping for garanties be a letter/symbol.
        if (!(std::cin >> position)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a valid number";
            continue; // goes back to the begining of the loop
        }

        auto it = std::find(legal_moves.begin(), legal_moves.end(), position);
        
        if (it != legal_moves.end()) break;
        else std::cout << "Occupied or invalid Position! Try Again!";

    }

    return position
}

void HumanAgent::print_board(const std::string& state) const {

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) std::cout << "\n" << "------" << std::endl;
        std::cout << state[i] << " ";
    }

    std::cout << "\n" << "------" << std::endl;

}