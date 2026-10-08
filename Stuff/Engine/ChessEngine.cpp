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

    turn_complete = false;
    player_colour = 0;
    calc_all_legal_moves(player_colour);
    
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
            if (event.key.keysym.scancode == SDL_SCANCODE_E)
            {
                int i = 0;
                for (square sqr : board[coord_to_index(selected_square.x,selected_square.y)]->get_legal_moves())
                {
                    sqr.print_pos();
                    i++;
                }
                if (i == 0) {std::cout << "None" << std::endl;}
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

    if (turn_complete == true && checkmate == false)
    {
        turn_complete = false;
        player_colour = !player_colour;

        calc_all_legal_moves(player_colour);

        checkmate = check_checkmate(player_colour);
        std::cout << "======================" << std::endl;
        if (checkmate == true)
        {
            std::cout << "GAME OVER" << std::endl;
        }
    }

}

void Chess::calc_all_legal_moves(int clr_i)
 {
    for (Piece* p : board)
    {
        if (p != nullptr && p->clr_index == clr_i) {p->calculate_legal_moves(false);} 
    }
 }

bool Chess::check_checkmate(int clr_i)
{
    for (int i = 0; i <= 63; i++)
    {
        if (board[i] == nullptr || board[i]->clr_index != clr_i) {continue;}
        else if (board[i]->get_legal_moves().size() != 0) {return false;}
    }
    return true;
}