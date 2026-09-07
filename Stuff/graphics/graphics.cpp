#include <iostream>

#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "../Engine/ChessEngine.hpp"
#include "graphics.hpp"

using namespace std;

program_graphics::program_graphics()  {}
program_graphics::~program_graphics() {}

int program_graphics::init(Chess* ChessEngine)
{
    int flags = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0 && (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        window = SDL_CreateWindow("Chess",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_SIZE,WINDOW_SIZE,flags);
        renderer = SDL_CreateRenderer(window,-1,0);
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

        square_size = WINDOW_SIZE / 8;

        string img_dir = "images/pieces/";
        white_imgs[0] = file_to_texture(img_dir + "White King.png");
        white_imgs[1] = file_to_texture(img_dir + "White Queen.png");
        white_imgs[2] = file_to_texture(img_dir + "White Rook.png");
        white_imgs[3] = file_to_texture(img_dir + "White Knight.png");
        white_imgs[4] = file_to_texture(img_dir + "White Bishop.png");
        white_imgs[5] = file_to_texture(img_dir + "White Pawn.png");
        
        black_imgs[0] = file_to_texture(img_dir + "Black King.png");
        black_imgs[1] = file_to_texture(img_dir + "Black Queen.png");
        black_imgs[2] = file_to_texture(img_dir + "Black Rook.png");
        black_imgs[3] = file_to_texture(img_dir + "Black Knight.png");
        black_imgs[4] = file_to_texture(img_dir + "Black Bishop.png");
        black_imgs[5] = file_to_texture(img_dir + "Black Pawn.png"); 

        chess_engine = ChessEngine;
        return 1;
    }
    return 0;
};
void program_graphics::draw_board()
{
    SDL_Rect square_rect;
    square_rect.w = square_size; square_rect.h = square_size;
    for (int y = 0; y <= 8; y++)
    {
        for (int x = 0; x <= 8; x++)
        {
            if (x % 2 == y % 2) {SDL_SetRenderDrawColor(renderer,155,155,155,155);} else {SDL_SetRenderDrawColor(renderer,0,100,0,255);}
            square_rect.x = x * square_size; square_rect.y = y * square_size;
            SDL_RenderDrawRect(renderer,&square_rect);
            SDL_RenderFillRect(renderer,&square_rect);
        }
    }
    for (int i = 0; i < 64; i++)
    {
        Piece* piece = chess.board[i];
        if (piece != nullptr)
        {
            int y = std::floor(i / 8);
            int x = i;
            if (i >= 8) {x = i - (y*8);}
            draw_piece(piece->clr_index,piece->piece_index,x,y);
        }
    }
}
SDL_Texture* program_graphics::file_to_texture(std::string path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface != NULL)
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
        return texture;    
    }
    else 
    {
        std::cout << "FAILED TO DRAW IMAGE" << std::endl;
        return nullptr;
    }
}

void program_graphics::draw_piece(int clr_index,int piece_index,int x,int y)
{
    SDL_Texture** array;
    if (clr_index == 0) {array = white_imgs;} else if (clr_index == 1) {array = black_imgs;}
    SDL_Rect rect;  
    rect.x = square_size*x; rect.y = square_size*y;
    rect.h = square_size; rect.w = square_size;
    SDL_RenderCopy(renderer,array[piece_index],NULL,&rect);

}

void program_graphics::update()
{   
    SDL_RenderClear(renderer);

    draw_board();
    SDL_RenderPresent(renderer);
}

void program_graphics::clean()
{
    for (SDL_Texture* texture : white_imgs) {SDL_DestroyTexture(texture);}
    for (SDL_Texture* texture : black_imgs) {SDL_DestroyTexture(texture);}
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}