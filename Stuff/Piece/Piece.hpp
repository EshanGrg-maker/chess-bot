#ifndef Piece_hpp
#define Piece_hpp

#include <iostream>
#include <vector>

#include "../square.hpp"

class Piece
{
    public:
        Piece(int piece_i,int clr_i, int board_index,Piece** board_arr);
        std::vector<square> calculate_legal_moves(bool return_val = false, bool x_ray = false);
        bool Move(int board_index);
        void force_move(int board_index);

        std::vector<square> get_legal_moves() {return legal_moves;}
        square get_square() {return current_square;}
        square get_last_square() {return last_square;}
        
        Piece* copy(Piece** board_ptr) {return new Piece(piece_index,clr_index,current_board_index,board_ptr);}

        bool in_check = false;
        bool last_moved = false;

        int piece_index = -1;
        int clr_index = -1;
    private:
        void push_legal_move(square to_sqr);
        
        square current_square; int current_board_index = -1;
        square last_square; int last_board_index = -1;

        std::vector<square> legal_moves;
        Piece** board;
};

#endif