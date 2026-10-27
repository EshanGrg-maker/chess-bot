#include <iostream>

#include "../ChessMath/ChessMath.hpp"

Piece::Piece(int piece_i,int clr_i, int board_index,Piece** board_arr) 
{
    piece_index = piece_i; 
    clr_index = clr_i; 
    index_to_coord(board_index,current_square.x,current_square.y);
    current_board_index = board_index;
    board = board_arr;
}


void calculate_bishop_moves(square current_square,int clr_index,Piece** board,bool x_ray,std::vector<square>* legal_moves)
{
    for (int delta_x = -1; delta_x <= 1; delta_x += 2)
    {
        for (int delta_y = -1; delta_y <= 1; delta_y += 2)
        {
            for (int mult = 1; mult <= 8; mult++)
            {
                int x = delta_x * mult; int y = delta_y * mult;

                square sqr = square(current_square.x + x,current_square.y + y);
                if (sqr.y < 0 || sqr.y >= 8 || sqr.x < 0 || sqr.x >= 8) {break;}
                int index = coord_to_index(sqr.x, sqr.y);
                if (board[index] != nullptr) 
                {
                    if (board[index]->clr_index == clr_index) {break;} 
                    else 
                    {
                        legal_moves->push_back(sqr);  
                        if (x_ray == false) {break;}
                    }
                } 
                else {legal_moves->push_back(sqr);}
            }
        }
    }
}
void calculate_rook_moves(square current_square,int clr_index,Piece** board,bool x_ray,std::vector<square>* legal_moves)
{
    for (int delta_x = - 1; delta_x <= 1; delta_x+=2)
    {
        for (int mult = 1; mult <= 8; mult++)
        {
            square sqr = square(current_square.x + (delta_x*mult),current_square.y);
            if (sqr.x < 0 || sqr.x >= 8 || sqr.y < 0 || sqr.y >= 8) {break;}
            int index = coord_to_index(sqr.x, sqr.y);
            if (board[index] != nullptr) 
            {
                if (board[index]->clr_index == clr_index) {break;} 
                else 
                {
                    legal_moves->push_back(sqr);  
                    if (x_ray == false) {break;}
                }
            } 
            else {legal_moves->push_back(sqr);}
        }
    }
    for (int delta_y = - 1; delta_y <= 1; delta_y+=2)
    {
        for (int mult = 1; mult <= 8; mult++)
        {
            square sqr = square(current_square.x,current_square.y + (delta_y*mult));
            if (sqr.x < 0 || sqr.x >= 8 || sqr.y < 0 || sqr.y >= 8) {break;}
            int index = coord_to_index(sqr.x, sqr.y);
            if (board[index] != nullptr) 
            {
                if (board[index]->clr_index == clr_index) {break;} 
                else 
                {
                    legal_moves->push_back(sqr);  
                    if (x_ray == false) {break;}
                }
            } 
            else {legal_moves->push_back(sqr);}
        }
    }
}

bool is_legal(int index_from, int index_to,Piece** board,int player_colour)
{
    Piece* king;
    Piece* copy_board[63];
    for (int i = 0; i <= 63; i++)
    {
        if (board[i] != nullptr)
        {
            copy_board[i] = board[i]->copy(copy_board);
            if (copy_board[i]->clr_index == player_colour && copy_board[i]->piece_index == 0)
            {
                king = copy_board[i];
            }
        } else { copy_board[i] = nullptr; }
    }
    copy_board[index_from]->force_move(index_to);

    square king_sqr = king->get_square();
    for (int i = 0; i <= 63; i++)
    {
        if (copy_board[i] != nullptr && copy_board[i]->clr_index != player_colour)
        {
            //std::cout << "ATTACK FROM: " << copy_board[i]->piece_index << " MOVING: " << board[index_from]->piece_index << std::endl;
            for (square sqr : copy_board[i]->calculate_legal_moves(true,false))
            {
                if (king_sqr.x == sqr.x && king_sqr.y == sqr.y)
                { 
                    std::string out;
                    for (int j = 0; j <= 63; j++)
                    {
                        if (j % 8 == 0) {out += "\n";}
                        if (j == index_from) {out += "XXX,";}
                        else if (copy_board[j] == nullptr) {out += "___,";}
                        else 
                        {
                            out += to_string(copy_board[j]->piece_index);
                            if (copy_board[j]->clr_index == 0) {out += "W";} else {out += "B";}
                            if (j == i) {out += "A,";}
                            else if (j == index_to) {out += "M,";}
                            else {out += "_,";}
                        }
                    }
                    //std::cout << out << std::endl;
                    return false; // moving this piece reveals a check on their king
                }
            }
        }
    }
    return true;
    // check if king is under attack after this move
}

void Piece::push_legal_move(square to_sqr)
{
    if (is_legal(current_board_index,coord_to_index(to_sqr.x,to_sqr.y),board,clr_index) == true)
    {
        legal_moves.push_back(to_sqr);
    }
}

std::vector<square> Piece::calculate_legal_moves(bool return_val,bool x_ray)
{
    std::vector<square> legal_m;
    switch (piece_index)
    {
        case 0: //king
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (x == 0 && y == 0) {continue;}
                    square sqr = square(current_square.x + x,current_square.y + y);
                    if (sqr.x < 0 || sqr.x >= 8 || sqr.y < 0 || sqr.y >= 8) {break;}
                    int index = coord_to_index(sqr.x, sqr.y);
                    if (board[index] != nullptr) {if (board[index]->clr_index == clr_index) {break;} else {legal_m.push_back(sqr);  break;}} 
                    else {legal_m.push_back(sqr);}    
                }


            }
            break;
        case 1: // queen
            calculate_rook_moves(current_square,clr_index,board,x_ray,&legal_m);
            calculate_bishop_moves(current_square,clr_index,board,x_ray,&legal_m);
            break;
        case 2: // rook
            calculate_rook_moves(current_square,clr_index,board,x_ray,&legal_m);
            break;
        case 3: // knight 
            for (int y = -2; y <= 2; y += 4)
            {
                for (int x = -1; x <= 1; x += 2)
                {
                    square sqr = square(current_square.x + x,current_square.y + y);
                    if (sqr.x < 0 || sqr.x >= 8 || sqr.y < 0 || sqr.y >= 8) {continue;}
                    int index = coord_to_index(sqr.x, sqr.y);
                    if (board[index] == nullptr || board[index]->clr_index != clr_index) {legal_m.push_back(sqr);} 
                }
            }  
            for (int x = -2; x <= 2; x += 4)
            {
                for (int y = -1; y <= 1; y += 2)
                {
                    square sqr = square(current_square.x + x,current_square.y + y);
                    if (sqr.x < 0 || sqr.x >= 8 || sqr.y < 0 || sqr.y >= 8) {continue;}
                    int index = coord_to_index(sqr.x, sqr.y);
                    if (board[index] == nullptr || board[index]->clr_index != clr_index) {legal_m.push_back(sqr);} 
                }                
            } 
            break;
        case 4: // bishop
            calculate_bishop_moves(current_square,clr_index,board,x_ray,&legal_m);
            break;
        case 5: // pawn
            if (current_square.y <= 0 || current_square.y >= 8) {break;}

            int delta_y = 1; 
            int limit = delta_y;
            if (clr_index == 0) {delta_y = -1;} else if (clr_index == 1) {delta_y = 1;}
            if (last_square.x == -1) {limit *= 2;}
            for (int y = delta_y; abs(y) <= limit; y += delta_y) // forwards movement 
            {
                square sqr = square(current_square.x,current_square.y + y);
                if (board[coord_to_index(sqr.x, sqr.y)] == nullptr) {legal_m.push_back(sqr);} else {break;}
            }
            for (int x = -1; x <= 1; x+=2) // diagonal taking + en passant
            {
                // checking to see if anything can be taken diagonally
                //if (x==0) {continue;}
                square sqr = square(current_square.x + x,current_square.y + delta_y);
                int index = coord_to_index(sqr.x, sqr.y);
                if (board[index] != nullptr && board[index]->clr_index != clr_index) {legal_m.push_back(sqr);} 

                // checking for enpassant
                index = coord_to_index(sqr.x,current_square.y);
                if (board[index] != nullptr && board[index]->clr_index != clr_index && board[index]->piece_index == piece_index)
                {
                    // checking if pawn just moved two squares#
                    square p_L_sqr = board[index]->get_last_square();
                    if (p_L_sqr.x != -1 && abs(current_square.y - p_L_sqr.y) == 2) 
                    {
                        sqr.x = p_L_sqr.x;
                        legal_m.push_back(sqr);
                    }
                }
            }
            
            break;
    }

    if (piece_index == 0)
    {
        if (last_square.x == -1) // castling  
        {
            square sqr_castle;
            sqr_castle.y = current_square.y;

            int kingside_i; int queen_side_i;
            if (clr_index == 0) {kingside_i = 63; queen_side_i = 56;}
            else if (clr_index == 1) {kingside_i = 7; queen_side_i = 0;}

            // starting to check if kingside castling is permitted
            if (board[kingside_i] != nullptr && board[kingside_i]->get_last_square().x == -1) // is kingside rook free?
            {
                //std::cout << 1 << std::endl;
                sqr_castle.x = current_square.x + 2;
                
                if (square_in_vector(square(sqr_castle.x - 1, sqr_castle.y),legal_moves) && (board[kingside_i-1] == nullptr && is_legal(current_board_index,kingside_i-1,board,clr_index)))
                {
                    std::cout << 2 << std::endl;
                    legal_m.push_back(sqr_castle);
                }
            }
            if (board[queen_side_i] != nullptr && board[queen_side_i]->get_last_square().x == -1) // queenside permitted
            {
                sqr_castle.x = current_square.x - 2;

                if (square_in_vector(square(sqr_castle.x + 1,sqr_castle.y),legal_moves) && (board[queen_side_i+2] == nullptr && is_legal(current_board_index,queen_side_i+2,board,clr_index)))
                {
                    legal_m.push_back(sqr_castle);
                }
            }
        }
    }
    
    if (return_val == false) 
    {
        legal_moves.clear();
        for (square sqr : legal_m)
        {
            push_legal_move(sqr);
        }
    }
    return legal_m;
};

void Piece::force_move(int board_index)
{
    last_square = current_square;
    index_to_coord(board_index,current_square.x,current_square.y);
    
    last_board_index = current_board_index;
    current_board_index = board_index;

    board[current_board_index] = board[last_board_index];
    board[last_board_index] = nullptr;

//    legal_moves.clear();
}

bool Piece::Move(int board_index)
{
    int move_index = -1; int i = 0;
    square move_sqr;
    for (square legal_move : legal_moves) 
    {
        if (coord_to_index(legal_move.x, legal_move.y) == board_index) {move_index = i; move_sqr = legal_move; break;} 
        i++;
    }

    if (move_index == -1) { return false; }

    // special stuff
    int move_offset = current_square.x - move_sqr.x;
    if (piece_index == 0 && abs(move_offset) == 2 ) // castling
    {
        square rk_sqr; rk_sqr.y = move_sqr.y;
        int rk_index;
        if (move_offset > 0) // queenside
        {
            rk_sqr.x = move_sqr.x + 1;
            rk_index = 56;
        }
        else // kingside 
        {
            rk_sqr.x = move_sqr.x - 1;
            rk_index = 63;
        }
        board[rk_index]->force_move(coord_to_index(rk_sqr.x,rk_sqr.y));
    }
    if (piece_index == 5 && board[board_index] == nullptr) // en passant
    {
        if (move_sqr.x - current_square.x != 0 )
        {
            int delta_y; if (clr_index == 0) {delta_y = 1;} else if (clr_index == 1) {delta_y = -1;}
            board[coord_to_index(move_sqr.x,move_sqr.y + delta_y)] = nullptr;
        }
    }
    // moving the piece
    force_move(board_index);

    return true;
}
