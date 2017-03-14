#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side)
{
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    
    board = new Board();
    cerr << sizeof(*board) << endl;
    this->side = side;
    
    if (side == BLACK)
    {
        opponentsSide = WHITE;
    }
    else if (side == WHITE)
    {
        opponentsSide = BLACK;
    }
}

/*
 * Destructor for the player.
 */
Player::~Player()
{
    delete board;
}

/**
 * Accessor function for test_minimax.cpp used to set the initial board state.
 *
 * @param data The data array that holds the initial board state.
 */
void Player::setBoard(char data[])
{
    board->setBoard(data);
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft)
{
    // Mark the opponent's move on the board.
    board->doMove(opponentsMove, opponentsSide);
    
    // Check whether there are valid moves left.
    if (!board->hasMoves(side))
    {
        return nullptr;
    }

    Move *bestMove = nullptr;
    int bestValue = INT_MIN;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move *move = new Move(i, j);
            
            if (board->checkMove(move, side))
            {
                Board *boardCopy = board->copy();
                boardCopy->doMove(move, side);

                // Use depth 2 for the minimax test and depth 6 in real
                // gameplay.
                int depth = testingMinimax ? 2 : 6;

                // no more bad_alloc, we just stop the recursion if it's too much memory used
                int currentValue = minimax(boardCopy, depth, INT_MIN, INT_MAX, opponentsSide);

                if(currentValue > bestValue || bestValue == INT_MIN) {
                    bestValue = currentValue;
                    bestMove = new Move(i, j);
                    delete move;
                }

                delete boardCopy;
            }

            else
            {
                delete move;
            }
        }
    }
    
    board->doMove(bestMove, side);
    
    return bestMove;
}

/**
 * @brief Use the minimax algorithm with alpha-beta pruning to assign a
 * heuristic value to a node (board state). At non-terminal nodes of maximum
 * search depth, a heuristic value is determined by using one of two possible
 * heuristic functions, depending on whether the algorithm is being tested.
 *
 * @param board The board state (node)
 * @param depth The depth of the node (how many levels of nodes below this node
 * to search)
 * @param side The side of the player whose turn it is
 * @param alpha The maximum heuristic value that the maximizing player is
 * assured of
 * @param beta The minimum heuristic value that the minimizing player is assured
 * of
 *
 * @return A heuristic value that represents the favorability of the node, where
 * larger values denote more favorable odds for this player and smaller values
 * denote less favorable odds for this player.
 */
int Player::minimax(Board *board, int depth, int alpha, int beta, Side side)
{
    if (depth == 0 || board->isDone())
    {
        if (testingMinimax)
        {
            // Use the standard heuristic for the minimax test that is the
            // difference of the number of stones this player has and the
            // number of stones the opponent has.
            return board->count(this->side) - board->count(this->opponentsSide);
        }

        // Otherwise, use the special heuristic implemented in board.cpp.
        return board->getHeuristic(this->side, this->opponentsSide);
    }
    
    // Determine the side of the opponent of the player whose turn it is.
    Side opponentsSide = (side == BLACK) ? WHITE : BLACK;
        
    if (this->side == side)
    {
        // It is the turn of this player, the maximizing player in minimax.
        
        int bestValue = INT_MIN;
        
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Move *move = new Move(i, j);
                
                if (board->checkMove(move, side))
                {
                    // no more bad_alloc hopefully
                    try {
                        Board *boardCopy = board->copy();
                        boardCopy->doMove(move, side);
                        int v = minimax(boardCopy, depth - 1, alpha, beta, \
                                    opponentsSide);
                        delete boardCopy;
                        bestValue = (v > bestValue) ? v : bestValue;
                    }
                    catch (std::bad_alloc) {
                        cerr << "one";
                        delete move;
                        return bestValue;
                    }

                    alpha = (alpha > bestValue) ? alpha : bestValue;
                                        
                    if (beta <= alpha)
                    {
                        // This node and all of its child nodes do not need
                        // to be examined.
                        break;
                    }
                }
                
                delete move;
            }
        }
        
        return bestValue;
    }
    else
    {
        // It is the turn of the opponent, the minimizing player in minimax.
        
        int bestValue = INT_MAX;
        
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Move *move = new Move(i, j);
                
                if (board->checkMove(move, side))
                {
                    // no more bad_alloc hopefully
                    try {
                        Board *boardCopy = board->copy();
                        boardCopy->doMove(move, side);
                        int v = minimax(boardCopy, depth - 1, alpha, beta, \
                                    opponentsSide);
                        delete boardCopy;
                        bestValue = (v < bestValue) ? v : bestValue;
                    }
                    catch (std::bad_alloc) {
                        cerr << "two";
                        delete move;
                        return bestValue;
                    }

                    beta = (beta < bestValue) ? beta : bestValue;
                    
                    if (beta <= alpha)
                    {
                        // This node and all of its child nodes do not need
                        // to be examined.
                        break;
                    }
                }
                
                delete move;
            }
        }
        
        return bestValue;
    }
}
