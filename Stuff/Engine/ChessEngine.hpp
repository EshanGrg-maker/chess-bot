class Piece
{
    public:
        Piece(int piece_i,int clr_i) {piece_index = piece_i; clr_index = clr_i;}
        int piece_index = -1;
        int clr_index = -1;
};
struct square
{
    int x = -1; int y = -1;
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
    private:
        void check_events();
        void reset_board();

        square selected_square;
        bool running = true;
};
