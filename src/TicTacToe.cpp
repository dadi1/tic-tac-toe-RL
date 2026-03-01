#include "../include/TicTacToe.hpp"

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

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
        else if (sum == -3) return -1;
    }

    return 0;
}

void TicTacToe::print_board() const {
    
    for (int i = 0; i < 9; i++) {
        if (i%3 == 0) std::cout << "\n" <<  "------" << std::endl;
        std::cout << board[i] << " ";
    }
    std::cout << "\n" <<  "------" << std::endl;
}

void TicTacToe::print_board_symbol() const {
    std::string symbol;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) symbol = "_";
        if (board[i] == 1) symbol = "X";
        if (board[i] == -1) symbol = "O";
        if (i % 3 == 0) std::cout << "\n" << "------" << std::endl;

        std::cout << symbol << " ";
    }
    std::cout << "\n" << "------" << std::endl; 
}

bool TicTacToe::play_move(int position) {

    std::vector<int> legal_moves = get_legal_moves();

    auto it = std::find(legal_moves.begin(), legal_moves.end(), position);

    if (it == legal_moves.end()) return false;

    board[position] = current_player;
    current_player *= -1;
    move_count++;

    return true;
}