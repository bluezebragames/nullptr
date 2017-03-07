#ifndef __COMMON_H__
#define __COMMON_H__

enum Side
{ 
    WHITE, BLACK
};

class Move
{   
    public:
        Move(int x, int y)
        {
            this->x = x;
            this->y = y;        
        }
        
        ~Move() {}

        int getX() { return x; }
        int getY() { return y; }
        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }

    private:
        int x, y;
};

#endif
