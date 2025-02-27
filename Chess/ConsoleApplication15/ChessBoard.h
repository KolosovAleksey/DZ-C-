#pragma once
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPiece.h"
#include <iostream>
#include <string>
using namespace std;

class ChessBoard {
private:
    ChessPiece* board[8][8];
    string currentPlayer;

public:
    ChessBoard();
    ~ChessBoard();

    void initializeBoard();
    void displayBoard() const;
    bool movePiece(const string& from, const string& to);
    string getCurrentPlayer() const;
    void switchPlayer();
};

#endif
