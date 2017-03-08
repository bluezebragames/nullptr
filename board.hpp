#ifndef __BOARD_H__
#define __BOARD_H__
#define NUM_SPACES 64
#define CORNER 5
#define CORNER_ADJ -2
#define CORNER_DIAG -5

#include <bitset>
#include "common.hpp"

using namespace std;

class Board
{
    public:
        Board();
        ~Board();
        Board *copy();

        bool isDone();
        bool hasMoves(Side side);
        bool checkMove(Move *m, Side side);
        void doMove(Move *m, Side side);
        int count(Side side);
        int countBlack();
        int countWhite();
        void setBoard(char data[]);
        int getHeuristic(Side side, Side opponentsSide);

    private:
        bitset<NUM_SPACES> black;
        bitset<NUM_SPACES> taken;

        bool occupied(int x, int y);
        bool get(Side side, int x, int y);
        void set(Side side, int x, int y);
        bool onBoard(int x, int y);
};

#endif
