#include "./include/Arena.hpp"
#include "./include/HumanAgent.hpp"
#include "./include/RLAgent.hpp"

int main() {
    HumanAgent humano;

    RLAgent robo_inteligente(0.1, 0.9, 0.0);

    robo_inteligente.load_model("../models/q_table_v3.txt");

    Arena arena;

    arena.play_match(&humano, &robo_inteligente);

    return 0;
}
//  g++ main.cpp ./src/Arena.cpp ./src/TicTacToe.cpp ./src/RLAgent.cpp ./src/HumanAgent.cpp -o play_game