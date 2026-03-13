#pragma once

#include "../include/Arena.hpp"
#include "../include/RLAgent.hpp"
#include "../include/RandomAgent.hpp"

#include <string>

class TrainingArena : public Arena {
private:
    TicTacToe game;
    
public:

    TrainingArena() = default;

    void train_vs_random(int total_episodes, const std::string& filename);

    void train_self_play(int total_episodes, const std::string& filename);

};