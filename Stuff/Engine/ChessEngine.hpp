#include <iostream>
#include <string>
#include <vector>

#include "../ChessMath/ChessMath.hpp"

struct square
{
    square(int X = -1, int Y = -1) {x = X; y = Y;}
    std::string row_letters[8] = {"a","b","c","d","e","f","g","h"};
    void print_pos() {std::cout << row_letters[x] << 8 - y << std::endl;}

    int x = -1; int y = -1;
};

class Piece
{
    public:
        Piece(int piece_i,int clr_i, int board_index,Piece** board_arr) 
        {
            piece_index = piece_i; 
            clr_index = clr_i; 
            index_to_coord(board_index,current_square.x,current_square.y);
            current_board_index = board_index;
            board = board_arr;
        }
        void calculate_legal_moves();
        bool Move(int board_index);
        void force_move(int board_index);

        std::vector<square> get_legal_moves() {return legal_moves;}
        square get_square() {return current_square;}
        square get_last_square() {return last_square;}

        bool last_moved = false;

        int piece_index = -1;
        int clr_index = -1;
    private:
        square current_square; int current_board_index = -1;
        square last_square; int last_board_index = -1;

        std::vector<square> legal_moves;
        Piece** board;
};

class Chess
{
    public:
        Piece* board[64];
        Chess();
        ~Chess();

        void update();
        void complete_turn() {turn_complete = true;}

        bool is_running() {return running;}
        square GetSelectedSquare() {return selected_square;}
        std::vector<square> get_highlight_squares() {return highlight_squares;}
        Piece* get_last_moved_piece() {return last_moved_piece;}
    private:
        void check_events();
        void handle_mouse_input(SDL_MouseButtonEvent& event);

        void reset_board();

        square selected_square;
        std::vector<square> highlight_squares;

        Piece* last_moved_piece = nullptr;

        int player_colour = 0;
        bool turn_complete = false;
        bool running = true;
};
