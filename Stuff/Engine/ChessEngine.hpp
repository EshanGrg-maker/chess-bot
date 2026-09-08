#include <iostream>
#include <vector>

struct square
{
    square(int X = -1, int Y = -1) {x = X; y = Y;}
    int x = -1; int y = -1;
};

class Piece
{
    public:
        Piece(int piece_i,int clr_i, int board_index) 
        {
            piece_index = piece_i; 
            clr_index = clr_i; 
            current_square.y = std::floor(board_index / 8);
            int x = board_index;
            if (board_index >= 8) {x = board_index - (current_square.y*8);}
            current_square.x = x;
        }
        void calculate_legal_moves();
        void Move();

        std::vector<square> get_legal_moves() {return legal_moves;}
        square get_square() {return current_square;}

        int piece_index = -1;
        int clr_index = -1;
    private:
        square current_square;
        square last_square;

        std::vector<square> legal_moves;
};

class Chess
{
    public:
        Piece* board[64];
        Chess();
        ~Chess();

        void update();

        bool is_running() {return running;}
        square GetSelectedSquare() {return selected_square;}
        std::vector<square> get_highlight_squares() {return highlight_squares;}
    private:
        void check_events();
        void handle_mouse_input(SDL_MouseButtonEvent& event);

        void reset_board();

        square selected_square;
        std::vector<square> highlight_squares;

        int player_colour = 0;
        bool running = true;
};
