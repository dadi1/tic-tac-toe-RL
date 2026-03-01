#include "../include/TicTacToe.hpp"

class SoloGame{
private:
    int player_one = 1;
    int player_two = -1;
    TicTacToe game;

public:
    SoloGame() {}

    int play_round();

    int get_move_from_terminal();

    void player_turn(int player);

};