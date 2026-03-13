#include "../include/RLAgent.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <string>

// Constructor.
RLAgent::RLAgent(double alpha, double gamma, double epsilon)
    : alpha(alpha), gamma(gamma), epsilon(epsilon) {
    std::random_device rd;
    rng = std::mt19937(rd());
}

    
void RLAgent::ensure_state_exists(const std::string& state) {
    if (q_table.find(state) == q_table.end()) {
        q_table[state] = std::vector<double>(9,0.0);
    }
}

int RLAgent::choose_action(const std::string& state, const std::vector<int>& legal_moves) {
    if (legal_moves.empty()) throw std::runtime_error("No aveilable move for the agent to choose.");

    ensure_state_exists(state);

    std::uniform_real_distribution<double> dist_double(0.0, 1.0);
    double explore_chance = dist_double(rng);

    // Exploration for epsilon greedy action.
    if (explore_chance < epsilon) {
        std::uniform_int_distribution<int> dist_int(0, legal_moves.size() -1);
        int random_index = dist_int(rng);
        return legal_moves[random_index];
    }

    // Explotation.  
    double max_q_value = -99999.0;
    double current_q;
    int best_action = legal_moves[0];

    for (int move : legal_moves) {
        current_q = q_table[state][move];
        if (current_q > max_q_value) {
            max_q_value = current_q;
            best_action = move;
        }
    }

    return best_action;
}

void RLAgent::learn(const std::string& state, int action, double reward, const std::string& next_state, const std::vector<int>& next_legal_moves) {

    ensure_state_exists(state);

    double max_next_q = 0.0;

    if (!next_legal_moves.empty()) {
        ensure_state_exists(next_state);

        max_next_q = -99999,0;

        for (int move : next_legal_moves) {
            if (q_table[next_state][move] > max_next_q)
                max_next_q = q_table[next_state][move];
        }
    }

    double current_q = q_table[state][action];

    q_table[state][action] = current_q + alpha * (reward + gamma * max_next_q - current_q);
}

void RLAgent::save_model(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: was not possibel to save the file." << std::endl;
        return;
    }

    for (const auto& pair: q_table) {
        file << pair.first;
        for (double q_value : pair.second) {
            file << " " << q_value;
        }
        file << "\n";
    }

    file.close();
    std::cout << "Model saved with Success!! (" << q_table.size() << " states) em: " << filename << std::endl;
}

void RLAgent::load_model(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Warning!: file " << filename << "was not found!" << std::endl;
        return;
    }
    
    q_table.clear();
    std::string state;

    while (file >> state) {
        std::vector<double> q_values(9);
        for (int i = 0; i < 9; i++) {
            file >> q_values[i];
        }
        q_table[state] = q_values;

    }

    file.close();
    std::cout << "Model was loaded with success (" << q_table.size() << " states) from: " << filename << std::endl;
}
