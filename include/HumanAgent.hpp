#pragma once

#include "../include/Agent.hpp"

class HumanAgent: public Agent {
private:

public:
    HumanAgent() = default;

    int choose_action(const std::string& state, const std::vector<int>& legal_moves) override;

    void print_board(const std::string& state) const;
    
}; // HumanAgent class