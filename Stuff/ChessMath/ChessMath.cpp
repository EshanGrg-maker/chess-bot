#include <iostream>
#include <math.h>

#include <string.h>
#include <SDL2/SDL_rect.h>

#include "../Piece/Piece.hpp"

void index_to_coord(int index, int& Xptr, int& Yptr)
{
            int y = std::floor(index / 8);
            int x = index;
            if (index >= 8) {x = index - (y*8);}
            
            Xptr = x; Yptr = y;
}
int coord_to_index(int x, int y) { return (y*8) + x; }

void center_rect(SDL_Rect &rect, const int x, const int y)
{
    // positions the rect so that its center lies on {x,y}
    rect.x = x - (rect.w / 2);
    rect.y = y - (rect.y / 2);
}