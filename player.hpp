#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <climits>
#include "board.hpp"

<<<<<<< HEAD
class Player
{
    public:
        Player(Side side);
        ~Player();
=======

class Player {
>>>>>>> bd1f63732238af0180683d9002a209cae60517e8

        Move *doMove(Move *opponentsMove, int msLeft);
        void setBoard(char data[]);

        // Flag to tell if the player is running within the test_minimax context
        bool testingMinimax;
        
        // Indicator that tells which side the player is on.
        Side side;
        
        // Indicator that tells which side the opponent is on.
        Side opponentsSide;

<<<<<<< HEAD
    private:
        int minimax(Board *board, int depth, Side side);
        
        // The player's representation of the board.
        Board *board;
=======
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    Board board;
    Side ourSide, theirSide;
>>>>>>> bd1f63732238af0180683d9002a209cae60517e8
};

#endif
