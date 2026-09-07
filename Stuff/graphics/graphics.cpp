#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "graphics.hpp"

program_graphics::program_graphics()  {}
program_graphics::~program_graphics() {}

int program_graphics::init()
{
    int flags = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0 && (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        window = SDL_CreateWindow("Chess",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_SIZE,WINDOW_SIZE,flags);
        renderer = SDL_CreateRenderer(window,-1,0);
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

        square_size = WINDOW_SIZE / 8;

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
            if (x % 2 == y % 2) {SDL_SetRenderDrawColor(renderer,255,255,255,255);} else {SDL_SetRenderDrawColor(renderer,0,100,0,255);}
            square_rect.x = x * square_size; square_rect.y = y * square_size;
            SDL_RenderDrawRect(renderer,&square_rect);
            SDL_RenderFillRect(renderer,&square_rect);
        }
    }
}
void program_graphics::draw_image(std::string img_path,int x,int y,int w,int h) 
{
    SDL_Surface* surface = IMG_Load(img_path.c_str());
    if (surface != NULL)
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_Rect rect;
        rect.x = x; rect.y = y; rect.h = h; rect.y = y;
        SDL_RenderCopy(renderer,texture,NULL,&rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void program_graphics::check_events()
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

void program_graphics::update()
{   
    SDL_RenderClear(renderer);

    draw_board();

    SDL_RenderPresent(renderer);


    check_events();
}