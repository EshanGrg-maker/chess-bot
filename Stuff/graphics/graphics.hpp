#include <SDL2/SDL.h>

class program_graphics
{
    public:
        program_graphics();
        ~program_graphics();
        int init();

        bool is_running() {return running;}
        void update();
    private:
        void draw_board();
        void check_events();

        const int WINDOW_SIZE = 600;
        int square_size;

        bool running = true;

        SDL_Window *window;
        SDL_Renderer *renderer;
};