#include "../include/SoloGame.hpp"

#include <iostream>

int SoloGame::play_round() {

    while(!game.is_terminal()) {
        game.print_board_symbol();
        player_turn(game.get_current_player());
    }
    game.print_board_symbol();

    int winner = game.check_winner();

    if (winner == 1)  std::cout << "Player 1 won the Round!." << std::endl;
    if (winner == -1) std::cout << "Player 2 won the Round!." << std::endl;
    if (winner == 0)  std::cout << "That's a Drawn!" << std::endl;

    return winner;
}

void SoloGame::player_turn(int player) {
    
    if (player == 1) std::cout <<  "Player 1 (X) turn: make your play!" << std::endl;
    if (player == -1) std::cout << "Player 2 (O) turn: make your play!" << std::endl;

    int position;
    std::cin >> position;
    while(!game.play_move(position)) {
        std::cout << "This Decision was already made, try again!" << std::endl;
        std::cin >> position;
    }

}   