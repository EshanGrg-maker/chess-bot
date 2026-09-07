#include "ChessEngine.hpp"
#include <SDL2/SDL.h>

Chess::~Chess() {};
Chess::Chess() 
{
    reset_board();
};

void Chess::reset_board()
{
    for (int i = 0; i < 64; i++) {board[i] = nullptr;}
    board[0] = new Piece(2,1);
    board[1] = new Piece(3,1);
    board[2] = new Piece(4,1);
    board[3] = new Piece(1,1);
    board[4] = new Piece(0,1);
    board[5] = new Piece(4,1);
    board[6] = new Piece(3,1);
    board[7] = new Piece(2,1);
    for (int i = 8; i <= 15; i++) {board[i] = new Piece(5,1);}

    board[56] = new Piece(2,0);
    board[57] = new Piece(3,0);
    board[58] = new Piece(4,0);
    board[59] = new Piece(1,0);
    board[60] = new Piece(0,0);
    board[61] = new Piece(4,0);
    board[62] = new Piece(3,0);
    board[63] = new Piece(2,0); 
    for (int i = 48; i <= 55; i++) {board[i] = new Piece(5,0);}
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
    }
}