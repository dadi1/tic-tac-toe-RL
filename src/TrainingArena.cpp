#include "../include/TrainingArena.hpp"

#include <iostream>
#include <vector>
#include <string>

void TrainingArena::train_vs_random(int total_episodes, const std::string& filename) {

    // Initializes Reinforcement Learning.
    RLAgent rl_agent(0.1, 0.9, 0.3);
    rl_agent.load_model(filename);

    // Initializes Random Agent.
    RandomAgent random_agent;

    TicTacToe game;

    std::cout << "Initializing Training with : " << total_episodes << " episodes" << std::endl;

    for (int episode = 0; episode < total_episodes; episode++) {
        // Resets the board.
        game.reset();

        std::string last_state = "";
        int last_action = -1;
        bool is_first_turn = true;

        while (!game.is_terminal()) {

            // RL agent turn.
            if(game.get_current_player() == 1) {
                std::string current_state = game.get_canonical_state();
                std::vector<int> legal_moves = game.get_legal_moves();

                int action = rl_agent.choose_action(current_state, legal_moves);

                if (!is_first_turn) {
                    rl_agent.learn(last_state, last_action, 0.0, current_state, legal_moves);
                }

                last_state = current_state;
                last_action = action;
                is_first_turn = false;

                game.play_move(action);
            }
            // Random Agent turn.
            else {
                std::string current_state = game.get_canonical_state();
                std::vector<int> legal_moves = game.get_legal_moves();

                int action = random_agent.choose_action(current_state, legal_moves);
                game.play_move(action);
            }
        }

        int winner = game.check_winner();
        double final_reward = 0.0;

        if (winner == 1) final_reward = 1.0;
        else if (winner == -1) final_reward = -1.0;
        
        std::vector<int> empty_moves;
        rl_agent.learn(last_state, last_action, final_reward, "TERMINAL", empty_moves);

        if ((episode + 1) % 20000 == 0) {
            std::cout << "Episode " << (episode + 1) << " concluded, in " << 100 * (double(episode) + 1) / double(total_episodes) << "% completed" << std::endl;

        }
    }

    rl_agent.save_model(filename);
    std::cout << "Training concluded with Success!!" << std::endl;
}