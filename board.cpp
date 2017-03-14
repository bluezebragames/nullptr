#include <iostream>
#include "board.hpp"

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board()
{
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
    
    moves_made = 0;
}

/*
 * Destructor for the board.
 */
Board::~Board()
{
    
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy()
{
    Board *newBoard;
    try {
        newBoard = new Board();
    }
    catch (std::bad_alloc) {
    }
    newBoard->black = black;
    newBoard->taken = taken;
    newBoard->moves_made = moves_made;
    return newBoard;
}

bool Board::occupied(int x, int y)
{
    return taken[x + 8 * y];
}

bool Board::get(Side side, int x, int y)
{
    return occupied(x, y) && (black[x + 8 * y] == (side == BLACK));
}

void Board::set(Side side, int x, int y)
{
    taken.set(x + 8 * y);
    black.set(x + 8 * y, side == BLACK);
}

bool Board::onBoard(int x, int y)
{
    return (0 <= x && x < 8 && 0 <= y && y < 8);
}


/*
 * Returns true if the game is finished; false otherwise. The game is finished
 * if neither side has a legal move.
 */
bool Board::isDone()
{
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move move(i, j);
            
            if (checkMove(&move, side)) return true;
        }
    }
    
    return false;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side)
{
    // Passing is only legal if you have no moves.
    if (m == nullptr) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            
            if (onBoard(x, y) && get(other, x, y))
            {
                do
                {
                    x += dx;
                    y += dy;
                }
                while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side)
{
    // A nullptr move means pass.
    if (m == nullptr) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do
            {
                x += dx;
                y += dy;
            }
            while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y))
            {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                
                while (onBoard(x, y) && get(other, x, y))
                {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    
    set(side, X, Y);

    // wow we've made another move, might as well add it in
    moves_made++;    
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side)
{
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack()
{
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite()
{
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[])
{
    taken.reset();
    black.reset();
    
    for (int i = 0; i < NUM_SPACES; i++)
    {
        if (data[i] == 'b')
        {
            taken.set(i);
            black.set(i);
        }
        
        if (data[i] == 'w')
        {
            taken.set(i);
        }
    }
}


/**
 * @brief Assign a value to the current state of the board from the
 * perspective of the player 'side.'
 *
 * @param side The side of the player for which the heuristic is being
 * evaluated.
 * @param opponentsSide The side of the opponent of the player for which the
 * heuristic is being evaluated.
 *
 * @return A heuristic value that represents the favorability of the board,
 * where larger values denote more favorable odds for the player who is on side
 * 'side' and smaller values denote less favorable odds for the player who is on
 * side 'side'.
 */
int Board::getHeuristic(Side side, Side opponentsSide)
{
    int is_black = (side == BLACK) ? 1 : -1;
    int score = TOKEN_DIFF_WEIGHT * (this->count(side) - this->count(opponentsSide));

    if(moves_made <= 50) { // token diff is the only thing that matters late-game
        for(int i = 0; i<BOARD_SIZE; ++i) {
            for(int j = 0; j<BOARD_SIZE; ++j) {
                if(occupied(i,j)) {
                    // square-value heuristics
                    score += black[BOARD_SIZE * i + j] ?
                             (is_black * HEURISTIC[i][j]) :
                             (is_black * -1 * HEURISTIC[i][j]);
                }
                else {
                    // frontier squares: subtract 3 for each open square next to one of our pieces
                    bool has_neighbor = hasNeighbor(i, j, side == BLACK);
                    score -= NEIGHBOR_PENALTY * has_neighbor;
                }
            }
        }
    }

    return score;
}

bool Board::hasNeighbor(int i, int j, bool is_black) {
    for(int k = max(i-1, 0); k<min(i+1, 8); ++k) {
        for(int l = max(j-1, 0); l<min(j+1, 8); ++l) {
            if((is_black && black[BOARD_SIZE * k + l]) ||
               (!is_black && occupied(k, l) && !black[BOARD_SIZE * k + l])) {
                return true;
            }
        }
    }
    return false;
}
