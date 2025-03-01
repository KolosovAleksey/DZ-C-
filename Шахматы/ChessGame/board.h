#ifndef BOARD_H
#define BOARD_H
#include "piece.h"

class Board {
private:
    Piece* squares[8][8];
public:
    Board();
    ~Board();
    Board(const Board& other);
    Board& operator=(const Board& other);
    void initialize();
    void display() const;
    bool movePiece(int fromX, int fromY, int toX, int toY, bool isBlueTurn);
    Piece* getPiece(int x, int y) const;
    bool isKingInCheck(bool isBlue) const;
    bool isCheckmate(bool isBlue);
    bool canMove(bool isBlue);
};

#endif