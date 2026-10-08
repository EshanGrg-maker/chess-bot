#ifndef ChessEngine_hpp
#define ChessEngine_hpp

#include <iostream>
#include <string>
#include <vector>


#include "../square.hpp"
#include "../Piece/Piece.hpp"
#include "../ChessMath/ChessMath.hpp"

using namespace std;

class Chess
{
    public:
        Piece* board[64];
        Chess();
        ~Chess();

        void update();
        void complete_turn() {turn_complete = true;}

        bool is_running() {return running;}
        bool is_checkmate() {return checkmate;}

        square GetSelectedSquare() {return selected_square;}
        std::vector<square> get_highlight_squares() {return highlight_squares;}
        Piece* get_last_moved_piece() {return last_moved_piece;}

        int get_current_turn() {return player_colour;}
    private:
        void check_events();
        void handle_mouse_input(SDL_MouseButtonEvent& event);

        void reset_board();

        void calc_all_legal_moves(int clr_i);
        bool check_checkmate(int clr_i);
        square selected_square;
        std::vector<square> highlight_squares;

        Piece* last_moved_piece = nullptr;

        int player_colour = 0;
        bool turn_complete = false;
        
        bool checkmate = false;
        bool running = true;
};

#endif