#include "game/TicTacToe.hpp"
#include <vector>
#include <cmath>

int TicTacToe::check_winner() const {

    const int winning_lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Horizontal Lines.
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Vertical Lines.
        {0, 4, 8}, {2, 4, 6} // Diagonal Lines.
    };

    for (int i = 0; i < 8; i++) {
        int a = winning_lines[i][0];
        int b = winning_lines[i][1];
        int c = winning_lines[i][2];

        int sum = board[a] + board[b] + board[c];

        if (sum == 3) return 1;
        else if (sum == -3) return 1;
    }

    return 0;
}