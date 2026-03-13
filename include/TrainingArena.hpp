#pragma once

#include "../include/Arena.hpp"
#include "../include/RLAgent.hpp"
#include "../include/RandomAgent.hpp"

#include <string>

class TrainingArena : public Arena {
public:

    TrainingArena() = default;

    void train_vs_random(int total_episodes, const std::string& filename);

    void train_self_play(RLAgent* learner, int total_episodes, const std::string& filename);

};