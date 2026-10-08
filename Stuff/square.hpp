#ifndef square_hpp
#define square_hpp

#include <iostream>
#include <string>

using namespace std;

struct square
{
    square(int X = -1, int Y = -1) {x = X; y = Y;}
    std::string row_letters[8] = {"a","b","c","d","e","f","g","h"};
    void print_pos() {std::cout << row_letters[x] << 8 - y << std::endl;}

    int x = -1; int y = -1;
};

#endif