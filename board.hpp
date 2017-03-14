#ifndef __BOARD_H__
#define __BOARD_H__
#define NUM_SPACES 64
#define BOARD_SIZE 8
#define TOKEN_DIFF_WEIGHT 20
#define NEIGHBOR_PENALTY 3

#include <bitset>
#include "common.hpp"

using namespace std;

const int HEURISTIC[BOARD_SIZE][BOARD_SIZE] =
  {{ 100, -20,  10,   5,   5,  10, -20, 100},
   { -20, -50,  -2,  -2,  -2,  -2, -50, -20},
   {  10,  -2,  -1,  -1,  -1,  -1,  -2,  10},
   {   5,  -2,  -1,  -1,  -1,  -1,  -2,   5},
   {   5,  -2,  -1,  -1,  -1,  -1,  -2,   5},
   {  10,  -2,  -1,  -1,  -1,  -1,  -2,  10},
   { -20, -50,  -2,  -2,  -2,  -2, -50, -20},
   { 100, -20,  10,   5,   5,  10, -20, 100}};

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
        bool hasNeighbor(int i, int j, bool is_black);

    private:
        bitset<NUM_SPACES> black;
        bitset<NUM_SPACES> taken;

        bool occupied(int x, int y);
        bool get(Side side, int x, int y);
        void set(Side side, int x, int y);
        bool onBoard(int x, int y);

        int moves_made = 0;
};

#endif
