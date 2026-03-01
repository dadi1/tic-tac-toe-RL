#pragma once

#include "../include/Agent.hpp"

#include <random>

class RandomAgent: public Agent {
private:
    std::mt19937 rng;

public:    
    RandomAgent();

    int choose_action(const std::string& state, const std::vector<int>& legal_moves) override;

}; // Random Agent class