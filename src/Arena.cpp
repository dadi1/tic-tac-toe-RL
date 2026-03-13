#include "../include/Arena.hpp"

#include <iostream>

void Arena::play_match(Agent* player_x, Agent* player_o) {

    game.reset();
    while(!game.is_terminal()) {
        
        Agent* current_agent = (game.get_current_player() == 1) ? player_x : player_o;

        std::string canonic_state = game.get_canonical_state();
        std::vector<int> legal_moves = game.get_legal_moves();

        int action = current_agent->choose_action(canonic_state, legal_moves);
        game.play_move(action);
    }

    game.print_board_symbol();
    
    int winner = game.check_winner();

    if (winner == 1) std::cout << "Player X is the winner!" << std::endl;
    if (winner == -1) std::cout << "Player O is the winner!" << std::endl;
    if (winner == 0) std::cout << "That's a Draw!" << std::endl;

}

int Arena::play_match_result(Agent* player_x, Agent* player_o) {
    game.reset();
        while(!game.is_terminal()) {
        
        Agent* current_agent = (game.get_current_player() == 1) ? player_x : player_o;

        std::string canonic_state = game.get_canonical_state();
        std::vector<int> legal_moves = game.get_legal_moves();

        int action = current_agent->choose_action(canonic_state, legal_moves);
        game.play_move(action);
    }

    game.print_board_symbol();
    
    int winner = game.check_winner();

    if (winner == 1) return 1;
    if (winner == -1) return -1;
    if (winner == 0) return 0;

    return winner;
}
