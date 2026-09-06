#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>

#include "Stuff/graphics/graphics.hpp"

using namespace std;

int main(int argc, char * argv[])
{
    program_graphics *graphics = new program_graphics();
    graphics->init();

    while (graphics->is_running()) {
        graphics->update();
    }
    return 0;
}