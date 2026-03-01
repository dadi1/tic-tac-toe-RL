#include <vector>
#include <numeric>
#include <stdexcept>

class TicTacToe {
private:
    std::vector <int> board;
    int current_player;
    int move_count;

public:
    // Constructor
    TicTacToe(): board(9, 0), current_player(1), move_count(0) {}

    // Reseter
    void reset() {
        std::fill(board.begin(), board.end(), 0);
        current_player = 1;
        move_count = 0;
    }

    int get_current_player() const {return current_player;}

    const std::vector<int>& get_board() const {return board;}

    std::vector<int> get_legal_moves() const {
        std::vector<int> moves;
        moves.reserve(9);
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                moves.push_back(i);
            }
        }
        return moves;
    }

    int check_winner() const;
    
    bool is_terminal() const {return (check_winner() != 0 || move_count == 9);}

};