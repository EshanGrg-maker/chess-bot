#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "ChessEngine.hpp"

Chess::~Chess() {};
Chess::Chess() 
{
    reset_board();
};

void Chess::reset_board()
{
    for (int i = 0; i < 64; i++) {board[i] = nullptr;}
    board[0] = new Piece(2,1,0);
    board[1] = new Piece(3,1,1);
    board[2] = new Piece(4,1,2);
    board[3] = new Piece(1,1,3);
    board[4] = new Piece(0,1,4);
    board[5] = new Piece(4,1,5);
    board[6] = new Piece(3,1,6);
    board[7] = new Piece(2,1,7);
    for (int i = 8; i <= 15; i++) {board[i] = new Piece(5,1,i);}

    board[56] = new Piece(2,0,56);
    board[57] = new Piece(3,0,57);
    board[58] = new Piece(4,0,58);
    board[59] = new Piece(1,0,59);
    board[60] = new Piece(0,0,60);
    board[61] = new Piece(4,0,61);
    board[62] = new Piece(3,0,62);
    board[63] = new Piece(2,0,63); 
    for (int i = 48; i <= 55; i++) {board[i] = new Piece(5,0,i);}
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
    }
}
void Chess::handle_mouse_input(SDL_MouseButtonEvent& event)
{
    if (event.button == SDL_BUTTON_LEFT) 
    {
        int mouse_x; int mouse_y;
        Uint32 buttons = SDL_GetMouseState(&mouse_x,&mouse_y);

        int tile_index = (std::floor(mouse_y /(600/8))*8) + std::floor(mouse_x / (600/8));
        if (board[tile_index] != nullptr && board[tile_index]->clr_index == player_colour) 
        {
            selected_square.x = std::floor(mouse_x / (600/8));
            selected_square.y = std::floor(mouse_y /(600/8));

            board[tile_index]->calculate_legal_moves();
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
}


void Piece::calculate_legal_moves()
{
    legal_moves.clear();
    switch (piece_index)
    {
        case 5:
            int delta_y = -1;
            int limit = delta_y;
            if (last_square.x == -1) {limit *= 2;}
            for (int y = delta_y; y >= limit; y += delta_y) {legal_moves.push_back(square(current_square.x,current_square.y + y));}
            break;
    }
};

void Piece::Move()
{
    std::vector<square> legal_moves;
    switch (piece_index)
    {
        case 0:
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (x == 0 && y == 0) {continue;}
                    legal_moves.push_back(square(x,y));
                }
            }
            break;
        
    }

}