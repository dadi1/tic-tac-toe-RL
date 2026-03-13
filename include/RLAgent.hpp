#pragma once

#include "../include/Agent.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <random>
#include <fstream>

class RLAgent : public Agent {
private:
    // Q-table.
    std::unordered_map<std::string, std::vector<double>> q_table;

    // Hiperparameters.
    double alpha;
    double gamma;
    double epsilon;

    std::mt19937 rng;

    void ensure_state_exists(const std::string& state);

public:

    RLAgent(double alpha = 0.1, double gamma = 0.9, double episilon = 0.1);

    int choose_action(const std::string& state, const std::vector<int>& legal_moves) override;

    void learn(const std::string& state, int action, double reward, const std::string& next_state, const std::vector<int>& next_legal_moves);

    void save_model(const std::string& filename) const;

    void load_model(const std::string& filename);
};