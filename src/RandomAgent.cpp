#include "../include/RandomAgent.hpp"

#include <stdexcept>

RandomAgent::RandomAgent() {

    std::random_device rd;
    rng = std::mt19937(rd());

}

int RandomAgent::choose_action(const std::string& state, const std::vector<int>& legal_moves) {

    if (legal_moves.empty()) throw std::runtime_error("Error: Random Agent was called but there is no more legal moves.");

    std::uniform_int_distribution<int> dist(0, legal_moves.size() - 1);
    int random_index = dist(rng);
    
    return legal_moves[random_index];
}
