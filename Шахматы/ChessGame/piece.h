#ifndef PIECE_H
#define PIECE_H

class Board;

class Piece {
private:
    char symbol;
    bool isBlue;
public:
    Piece(char s, bool blue);
    char getSymbol() const;
    bool isBluePiece() const;
    virtual bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const;
};

#endif