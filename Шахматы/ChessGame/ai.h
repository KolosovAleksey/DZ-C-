#ifndef AI_H
#define AI_H

#include "board.h"

class AI {
public:
    AI(int depth);
    void makeMove(Board& board);
};

#endif