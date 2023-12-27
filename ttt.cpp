#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

void draw(std::vector<char>& board) {
    std::cout << "     |     |      \n";

    std::cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";

    std::cout << "_____|_____|_____ \n";
    std::cout << "     |     |      \n";

    std::cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";

    std::cout << "_____|_____|_____ \n";
    std::cout << "     |     |      \n";

    std::cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
    std::cout << "     |     |      \n";

    std::cout << "\n";
}

char get_winner(std::vector<char>& board) {
    if ((board[0] == board[1]) && (board[0] == board[2]) && (board[1] == board[2])) {
        return board[0];
    } else if ((board[3] == board[4]) && (board[4] == board[5]) && (board[3] == board[5])) {
        return board[3];
    } else if ((board[6] == board[7]) && (board[7] == board[8]) && (board[6] == board[8])) {
        return board[6];
    } else if ((board[0] == board[3]) && (board[0] == board[6]) && (board[3] == board[6])) {
        return board[0];
    } else if ((board[1] == board[4]) && (board[4] == board[7]) && (board[1] == board[7])) {
        return board[4];
    } else if ((board[2] == board[5]) && (board[5] == board[8]) && (board[2] == board[8])) {
        return board[5];
    } else if ((board[0] == board[4]) && (board[4] == board[8]) && (board[1] == board[8])) {
        return board[8];
    } else if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == board[6])) {
        return board[2];
    } else {
        return ' ';
    }
}

bool is_draw(std::vector<char>& board) {
    int winner = get_winner(board);

    if (winner == ' ') {
        for (const char& symbol : board) {
            if (symbol == ' ') {
                return false;
            }
        }

        return true;
    }

    return false;
}

std::vector<int> take_non_occupied(std::vector<char>& board) {
    std::vector<int> result;

    for (int i = 0; i < board.size(); i++) {
        if (board[i] == ' ') {
            result.push_back(i);
        }
    }

    return result;
}


int main() {
    srand (time(NULL));

    std::vector<char> board = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    char me, opponent;

    std::cout << "Choose X or O: ";
    std::cin >> me;

    if (me == 'X') {
        opponent = 'O';
    } else if (me == 'O') {
        opponent = 'X';
    } else {
        std::cout << "Invalid Input";
        return 1;
    }
    
    bool is_retaking = false;

    while (true) {
        int my_move;
        std::cout << "Make your move: ";
        std::cin >> my_move;
        
        if (board[my_move - 1] != ' ') {
            std::cout << "The spot is already taken.\n";
            is_retaking = true;
        } else {
            board[my_move - 1] = me;
            is_retaking = false;
        }

        if (is_retaking == false) {
            std::vector<int> non_occupied = take_non_occupied(board);
            int rand_non_occupied = non_occupied[rand() % non_occupied.size()];
            board[rand_non_occupied] = opponent;
        }

        char winner = get_winner(board);

        if (is_draw(board)) {
            std::cout << "Draw!";
            break;
        } else if (winner == ' ') {
            draw(board);
            continue;
        } else if (winner == opponent) {
            std::cout << "You lost!";
            break;
        } else if (winner == me) {
            std::cout << "You win!";
            break;
        }        
    }
    

    return 0;
}