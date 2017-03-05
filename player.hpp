#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <climits>
#include "board.hpp"

class Player
{
    public:
        Player(Side side);
        ~Player();

        Move *doMove(Move *opponentsMove, int msLeft);
        void setBoard(char data[]);

        // Flag to tell if the player is running within the test_minimax context
        bool testingMinimax;
        
        // Indicator that tells which side the player is on.
        Side side;
        
        // Indicator that tells which side the opponent is on.
        Side opponentsSide;

    private:
        int minimax(Board *board, int depth, Side side);
        
        // The player's representation of the board.
        Board *board;
};

#endif
