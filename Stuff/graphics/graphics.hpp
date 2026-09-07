#include <iostream>
#include <SDL2/SDL.h>

#include <string>
#include <map>

#include "../Engine/ChessEngine.hpp"

class program_graphics
{
    public:
        program_graphics();
        ~program_graphics();
        int init(Chess* ChessEngine);

        void update();
        void clean();
    private:
        Chess chess;
        void draw_board();
        void draw_piece(int clr_index,int piece_index,int x,int y);
        SDL_Texture* file_to_texture(std::string path);

        const int WINDOW_SIZE = 600;
        int square_size;

        SDL_Texture* black_imgs[6];
        SDL_Texture* white_imgs[6];

        Chess* chess_engine;

        SDL_Window *window;
        SDL_Renderer *renderer;
};