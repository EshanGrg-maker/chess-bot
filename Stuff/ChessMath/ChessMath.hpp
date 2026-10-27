#ifndef ChessMath_hpp
#define ChessMath_hpp

#include <vector>
#include <SDL2/SDL_rect.h>

#include "../square.hpp"
#include "../Piece/Piece.hpp"

void index_to_coord(int index, int& Xptr, int& Yptr);
int coord_to_index(int x, int y);

void center_rect(SDL_Rect &rect, const int x, const int y);

bool square_in_vector(square sqr, vector<square> vect);
#endif