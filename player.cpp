#include <vector>
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
<<<<<<< HEAD
    board = new Board();
    this->side = side;
    
    if (side == BLACK)
    {
        opponentsSide = WHITE;
    }
    else if (side == WHITE)
    {
        opponentsSide = BLACK;
=======

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    // not much here yet, just setting up who is playing which side
    ourSide = side;
    if(ourSide == WHITE) {
        theirSide = BLACK;
    }
    else {
        theirSide = WHITE;
>>>>>>> bd1f63732238af0180683d9002a209cae60517e8
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
<<<<<<< HEAD
Move *Player::doMove(Move *opponentsMove, int msLeft)
{
    // Mark the opponent's move on the board.
    board->doMove(opponentsMove, opponentsSide);
    
    // Check whether there are valid moves left.
    if (!board->hasMoves(side))
    {
        return nullptr;
    }
    
    std::vector<Move*> possibles = std::vector<Move*>();
    std::vector<int> values = std::vector<int>();
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move *move = new Move(i, j);
            
            if (board->checkMove(move, side))
            {
                Board *boardCopy = board->copy();
                boardCopy->doMove(move, side);
                possibles.push_back(move);
                values.push_back(minimax(boardCopy, 2, opponentsSide));
                delete boardCopy;
            }
            
            else
            {
                delete move;
            }
        }
    }
    
    int maxValue = values[0];
    unsigned int maxValueIndex = 0;
    
    // Find the index of the move that maximized the heuristic value for this
    // player.
    for (unsigned int i = 0; i < values.size(); i++)
    {
        if (values[i] > maxValue)
        {
            maxValue = values[i];
            maxValueIndex = i;
        }
    }
    
    // Delete all moves except for the move with the maximum heuristic value.
    for (unsigned int i = 0; i < values.size(); i++)
    {
        if (i != maxValueIndex)
        {
            delete possibles[i];
        }
    }
    
    Move *bestMove = possibles[maxValueIndex];
    
    // Mark the player's move on the board.
    board->doMove(bestMove, side);
    
    return bestMove;
}

/**
 * Use the minimax algorithm to assign a heuristic value to a node (board
 * state). At non-terminal nodes of maximum search depth, a heuristic value is
 * determined by taking the difference of the number of stones that this player
 * has and the number of stones that the opponent has.
 *
 * @param board The board state (node)
 * @param depth The depth of the node (how many nodes below this node to search)
 * @param side The side of the player whose turn it is
 *
 * @return A heuristic value that represents the favorability of the node, where
 * larger values denote more favorable odds for this player and smaller values
 * denote less favorable odds for this player.
 */
int Player::minimax(Board *board, int depth, Side side)
{
    if (depth == 0 || board->isDone())
    {
        // Determine a heuristic value for this move by taking the difference of
        // the number of stones this player has and the number of stones the
        // opponent has.
        return board->count(this->side) - board->count(this->opponentsSide);
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
                    Board *boardCopy = board->copy();
                    boardCopy->doMove(move, side);
                    int v = minimax(boardCopy, depth - 1, opponentsSide);
                    bestValue = (v > bestValue) ? v : bestValue;
                    delete boardCopy;
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
                    Board *boardCopy = board->copy();
                    boardCopy->doMove(move, side);
                    int v = minimax(boardCopy, depth - 1, opponentsSide);
                    bestValue = (v < bestValue) ? v : bestValue;
                    delete boardCopy;
                }
                
                delete move;
            }
        }
        
        return bestValue;
    }
=======
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    // Make the opponent's move first
    if(opponentsMove != nullptr && opponentsMove->getX() > 0 && opponentsMove->getY() > 0) {
        // if they didn't pass or not make a move, that is
        // the opponent can not make a move only when we go first, I think?
        board.doMove(opponentsMove, theirSide);
    }

    vector<Move> possibleMoves;
    Move* toReturn = new Move(-1, -1);
    for(int i = 0; i<8; ++i) {
        for(int j = 0; j<8; ++j) {
            // if we can move here, add it to the list of possible moves
            Move curr = Move(i, j);
            if(board.checkMove(&curr, ourSide)) {
                possibleMoves.push_back(curr);
            }
        }
    }
    for(int i = 0; i<possibleMoves.size(); ++i) {
        cerr << possibleMoves[i].x << " " << possibleMoves[i].y << endl;
    }
    cerr << endl;

    if(possibleMoves.size() == 0) {
        return toReturn; // pass; there are no more available moves
    }
    toReturn->setX(possibleMoves[0].getX());
    toReturn->setY(possibleMoves[0].getY());
    //Move toReturn = possibleMoves[rand() * 1.0 * possibleMoves.size() / RAND_MAX];
    possibleMoves.clear();

    return new Move(toReturn->getX(), toReturn->getY());
>>>>>>> bd1f63732238af0180683d9002a209cae60517e8
}
