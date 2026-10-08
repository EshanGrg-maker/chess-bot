#ifndef graphics_hpp
#define graphics_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <map>


class program_graphics
{
    public:
        program_graphics();
        ~program_graphics();
        int init(Chess* ChessEngine);

        void update();
        void clean();
    private:
        void draw_board();
        void draw_piece(int clr_index,int piece_index,int x,int y);
        void draw_game_over();
        
        SDL_Texture* file_to_texture(std::string path);

        const int WINDOW_SIZE = 600;
        int square_size;

        SDL_Texture* black_imgs[6];
        SDL_Texture* white_imgs[6];

        TTF_Font* main_font;

        Chess* chess_engine;

        SDL_Window *window;
        SDL_Renderer *renderer;
        
};

#endif