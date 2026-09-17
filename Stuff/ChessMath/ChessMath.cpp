#include <math.h>

void index_to_coord(int index, int& Xptr, int& Yptr)
{
            int y = std::floor(index / 8);
            int x = index;
            if (index >= 8) {x = index - (y*8);}
            
            Xptr = x; Yptr = y;
}
int coord_to_index(int x, int y) { return (y*8) + x; }