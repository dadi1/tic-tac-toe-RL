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

        if ((episode + 1) % 500 == 0) {
            std::cout << "Episode " << (episode + 1) << " concluded, in " << 100 * (double(episode) + 1) / double(total_episodes) << "% completed" << std::endl;

        }
    }

    rl_agent.save_model(filename);
    std::cout << "Training concluded with Success!!" << std::endl;
}

void TrainingArena::train_self_play(int total_episodes, const std::string& filename) {
    std::cout << "Strating Self-Play training for " << total_episodes << " episodes" << std::endl;

    // Initializing RL agent.
    RLAgent learner(0.1, 0.9, 0.1);
    learner.load_model(filename);

    for (int episode = 0; episode < total_episodes; episode++) {
        game.reset();

        std::string last_state_1 = "", last_state_2 = "";
        int last_action_1 = -1, last_action_2 = -1;

        while(!game.is_terminal()) {
            int current_player = game.get_current_player();
            std::string current_state = game.get_canonical_state();
            std::vector<int> legal_moves = game.get_legal_moves();

            int action = learner.choose_action(current_state, legal_moves);
            
            if (current_player == 1) {
                if (last_action_1 != -1) {
                    learner.learn(last_state_1, last_action_1, 0.0, current_state, legal_moves);
                }
                last_state_1 = current_state;
                last_action_1 = action;
            }

            else {
                if (last_action_2 != -1) {
                    learner.learn(last_state_2, last_action_2, 0.0, current_state, legal_moves);
                }
                last_state_2 = current_state;
                last_action_2 = action;
            }

            game.play_move(action);
        }

        int winner = game.check_winner();
        double reward_1 = 0.0, reward_2 = 0.0;

        if (winner == 1) {
            reward_1 = 1.0;
            reward_2 = -1.0;
        } else if (winner == -1) {
            reward_1 = -1.0;
            reward_2 = 1.0;
        }

        std::vector<int> empty_moves;
        learner.learn(last_state_1, last_action_1, reward_1, "TERMINAL", empty_moves);
        learner.learn(last_state_2, last_action_2, reward_2, "TERMINAL", empty_moves);

        if ((episode + 1) % (total_episodes/500) == 0)
            std::cout << "Episode " << (episode + 1) << " concluded, in " << 100 * (double(episode) + 1) / double(total_episodes) << "% completed" << std::endl;
    }
    learner.save_model(filename);
    std::cout << "Self Training concluded with Success!!" << std::endl;
}