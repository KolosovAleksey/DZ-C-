#pragma once
#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include <string>
using namespace std;

class ChessPiece {
protected:
    string color;
    string name;

public:
    ChessPiece(const string& color, const string& name);
    virtual ~ChessPiece();

    virtual string getPossibleMoves(const string& currentPosition) const = 0;

    string getColor() const;

    string getName() const;

    void display() const;
};

class Pawn : public ChessPiece {
public:
    Pawn(const string& color);
    string getPossibleMoves(const string& currentPosition) const override;
};

class Rook : public ChessPiece {
public:
    Rook(const string& color);
    string getPossibleMoves(const string& currentPosition) const override;
};

class Knight : public ChessPiece {
public:
    Knight(const string& color);
    string getPossibleMoves(const string& currentPosition) const override;
};

class Bishop : public ChessPiece {
public:
    Bishop(const string& color);
    string getPossibleMoves(const string& currentPosition) const override;
};

class Queen : public ChessPiece {
public:
    Queen(const string& color);
    string getPossibleMoves(const string& currentPosition) const override;
};

class King : public ChessPiece {
public:
    King(const string& color);
    string getPossibleMoves(const string& currentPosition) const override;
};

#endif