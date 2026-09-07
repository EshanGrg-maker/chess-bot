#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>

#include "Stuff/Engine/ChessEngine.hpp"
#include "Stuff/graphics/graphics.hpp"

using namespace std;

int main(int argc, char * argv[])
{
    Chess *chess_engine = new Chess();
    program_graphics *graphics = new program_graphics();
    graphics->init(chess_engine);

    while (chess_engine->is_running()) {
        chess_engine->update();
        graphics->update();
    }

    graphics->clean();
    return 0;
}