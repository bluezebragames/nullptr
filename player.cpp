#include <vector>
#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

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
    }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
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
}
