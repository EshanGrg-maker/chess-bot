#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "ChessEngine.hpp"
#include "../ChessMath/ChessMath.hpp"

Chess::~Chess() {};
Chess::Chess() 
{
    reset_board();
};

void Chess::reset_board()
{
    for (int i = 0; i < 64; i++) {board[i] = nullptr;}
    board[0] = new Piece(2,1,0,board);
    board[1] = new Piece(3,1,1,board);
    board[2] = new Piece(4,1,2,board);
    board[3] = new Piece(1,1,3,board);
    board[4] = new Piece(0,1,4,board);
    board[5] = new Piece(4,1,5,board);
    board[6] = new Piece(3,1,6,board);
    board[7] = new Piece(2,1,7,board);
    for (int i = 8; i <= 15; i++) {board[i] = new Piece(5,1,i,board);}

    board[56] = new Piece(2,0,56,board);
    board[57] = new Piece(3,0,57,board);
    board[58] = new Piece(4,0,58,board);
    board[59] = new Piece(1,0,59,board);
    board[60] = new Piece(0,0,60,board);
    board[61] = new Piece(4,0,61,board);
    board[62] = new Piece(3,0,62,board);
    board[63] = new Piece(2,0,63,board); 
    for (int i = 48; i <= 55; i++) {board[i] = new Piece(5,0,i,board);}
};

void Chess::check_events()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) 
    {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            handle_mouse_input(event.button);
        case SDL_KEYDOWN:
            if (event.key.keysym.scancode == SDL_SCANCODE_P)
            {
                std::string out;
                for (int y = 0; y < 8; y++)
                {
                    for (int x = 0; x < 8; x++)
                    {
                        int index = coord_to_index(x, y);
                        if (board[index] != nullptr) {out += "O,";} else {out += "_,";}
                    }
                    out += "\n";
                }
                std::cout << out << std::endl;
            }
    }
}
void Chess::handle_mouse_input(SDL_MouseButtonEvent& event)
{
    if (event.button == SDL_BUTTON_LEFT) 
    {
        int mouse_x; int mouse_y;
        Uint32 buttons = SDL_GetMouseState(&mouse_x,&mouse_y);

        int tile_index = coord_to_index(std::floor(mouse_x / (600/8)), std::floor(mouse_y /(600/8)));
        if (board[tile_index] != nullptr && board[tile_index]->clr_index == player_colour) 
        {
            selected_square.x = std::floor(mouse_x / (600/8));
            selected_square.y = std::floor(mouse_y /(600/8));

            board[tile_index]->calculate_legal_moves();
        } else if (selected_square.x != -1)
        {
            Piece* selected_piece = board[coord_to_index(selected_square.x, selected_square.y)];
            if (selected_piece->Move(tile_index)) 
            {
                if (last_moved_piece != nullptr) {last_moved_piece->last_moved = false;}
                last_moved_piece = selected_piece;
                last_moved_piece->last_moved = true;
                selected_square = square();
                complete_turn();
            }
        }

    }
    else if (event.button == SDL_BUTTON_RIGHT)
    {
        int mouse_x; int mouse_y;
        Uint32 buttons = SDL_GetMouseState(&mouse_x,&mouse_y);

        mouse_x = std::floor(mouse_x / (600/8));
        mouse_y = std::floor(mouse_y /(600/8));       

        int i = 0; int original_vector_size = highlight_squares.size();
        for (square highlight : highlight_squares) // checking if tile is already highlighted
        {
            if (highlight.x == mouse_x && highlight.y == mouse_y) 
            {
                highlight_squares.erase(highlight_squares.begin() + i );
                break;
            }
            i++;
        }
        if (i == original_vector_size) {highlight_squares.push_back(square(mouse_x,mouse_y));}
    }
}

void Chess::update()
{
    check_events();

    if (turn_complete == true)
    {
        turn_complete = false;
        player_colour = !player_colour;
    }

}

void calculate_bishop_moves(square current_square,int clr_index,Piece** board,std::vector<square>* legal_moves)
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
                if (board[index] != nullptr) {if (board[index]->clr_index == clr_index) {break;} else {legal_moves->push_back(sqr);  break;}} 
                else {legal_moves->push_back(sqr);}
            }
        }
    }
}
void calculate_rook_moves(square current_square,int clr_index,Piece** board,std::vector<square>* legal_moves)
{
    for (int delta_x = - 1; delta_x <= 1; delta_x+=2)
    {
        for (int mult = 1; mult <= 8; mult++)
        {
            square sqr = square(current_square.x + (delta_x*mult),current_square.y);
            if (sqr.x < 0 || sqr.x >= 8 || sqr.y < 0 || sqr.y >= 8) {break;}
            int index = coord_to_index(sqr.x, sqr.y);
            if (board[index] != nullptr) {if (board[index]->clr_index == clr_index) {break;} else {legal_moves->push_back(sqr);  break;}} 
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
            if (board[index] != nullptr) {if (board[index]->clr_index == clr_index) {break;} else {legal_moves->push_back(sqr);  break;}} 
            else {legal_moves->push_back(sqr);}
        }
    }
}
void Piece::calculate_legal_moves()
{
    legal_moves.clear();
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
                    if (board[index] != nullptr) {if (board[index]->clr_index == clr_index) {break;} else {legal_moves.push_back(sqr);  break;}} 
                    else {legal_moves.push_back(sqr);}    

                    if (last_square.x == -1) // castling  
                    {
                        square sqr_castle;
                        sqr_castle.y = current_square.y;
                        if (board[63] != nullptr && board[63]->get_last_square().x == -1) // kingside permitted
                        {
                            sqr_castle.x = current_square.x + 2;
                            legal_moves.push_back(sqr_castle);
                        }
                        if (board[56] != nullptr && board[56]->get_last_square().x == -1) // queenside permitted
                        {
                            sqr_castle.x = current_square.x - 2;
                            legal_moves.push_back(sqr_castle);
                        }
                    }
                }
            }
            break;
        case 1: // queen
            calculate_rook_moves(current_square,clr_index,board,&legal_moves);
            calculate_bishop_moves(current_square,clr_index,board,&legal_moves);
            break;
        case 2: // rook
            calculate_rook_moves(current_square,clr_index,board,&legal_moves);
            break;
        case 3: // knight 
            for (int y = -2; y <= 2; y += 4)
            {
                for (int x = -1; x <= 1; x += 2)
                {
                    square sqr = square(current_square.x + x,current_square.y + y);
                    if (sqr.x < 0 || sqr.x >= 8 || sqr.y < 0 || sqr.y >= 8) {continue;}
                    int index = coord_to_index(sqr.x, sqr.y);
                    if (board[index] == nullptr || board[index]->clr_index != clr_index) {legal_moves.push_back(sqr);} 
                }
            }  
            for (int x = -2; x <= 2; x += 4)
            {
                for (int y = -1; y <= 1; y += 2)
                {
                    square sqr = square(current_square.x + x,current_square.y + y);
                    if (sqr.x < 0 || sqr.x >= 8 || sqr.y < 0 || sqr.y >= 8) {continue;}
                    int index = coord_to_index(sqr.x, sqr.y);
                    if (board[index] == nullptr || board[index]->clr_index != clr_index) {legal_moves.push_back(sqr);} 
                }                
            } 
            break;
        case 4: // bishop
            calculate_bishop_moves(current_square,clr_index,board,&legal_moves);
            break;
        case 5: // pawn
            if (current_square.y <= 0 || current_square.y >= 8) {return;}

            int delta_y = 1; 
            int limit = delta_y;
            if (clr_index == 0) {delta_y = -1;} else if (clr_index == 1) {delta_y = 1;}
            if (last_square.x == -1) {limit *= 2;}
            for (int y = delta_y; abs(y) <= limit; y += delta_y) // forwards movement 
            {
                square sqr = square(current_square.x,current_square.y + y);
                if (board[coord_to_index(sqr.x, sqr.y)] == nullptr) {legal_moves.push_back(sqr);} else {break;}
            }
            for (int x = -1; x <= 1; x+=2) // diagonal taking + en passant
            {
                // checking to see if anything can be taken diagonally
                //if (x==0) {continue;}
                square sqr = square(current_square.x + x,current_square.y + delta_y);
                int index = coord_to_index(sqr.x, sqr.y);
                if (board[index] != nullptr && board[index]->clr_index != clr_index) {legal_moves.push_back(sqr);} 

                // checking for enpassant
                index = coord_to_index(sqr.x,current_square.y);
                if (board[index] != nullptr && board[index]->clr_index != clr_index && board[index]->piece_index == piece_index)
                {
                    // checking if pawn just moved two squares#
                    square p_L_sqr = board[index]->get_last_square();
                    if (p_L_sqr.x != -1 && abs(current_square.y - p_L_sqr.y) == 2) 
                    {
                        sqr.x = p_L_sqr.x;
                        legal_moves.push_back(sqr);
                    }
                }
            }
            

            break;
    }
};

void Piece::force_move(int board_index)
{
    last_square = current_square;
    index_to_coord(board_index,current_square.x,current_square.y);
    
    last_board_index = current_board_index;
    current_board_index = board_index;

    board[current_board_index] = board[last_board_index];
    board[last_board_index] = nullptr;

    legal_moves.clear();
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
        
    }
    // moving the piece
    force_move(board_index);

    return true;
}