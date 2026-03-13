#pragma once

#include "../include/Agent.hpp"
#include "../include/TicTacToe.hpp"

class Arena {
private:
    TicTacToe game;

public:
    Arena() = default;
    void play_match(Agent* player_x, Agent* player_o);

    int play_match_result(Agent* player_x, Agent* player_o);

}; // Class Arena.