#include "piece.h"
#include "board.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Piece::Piece(char s, bool blue) : symbol(s), isBlue(blue) {}

char Piece::getSymbol() const {
    return symbol;
}

bool Piece::isBluePiece() const {
    return isBlue;
}

bool Piece::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    if (fromX == toX && fromY == toY) return false;
    if (toX < 0 || toX > 7 || toY < 0 || toY > 7) return false;

    Piece* target = board.getPiece(toX, toY);
    if (target && target->isBluePiece() == isBlue) return false;

    int dx = toX - fromX;
    int dy = toY - fromY;

    switch (symbol) {
    case 'P': // Пешка
        if (isBlue) { // Синие двигаются вверх
            if (fromX == 1 && toX == 3 && fromY == toY && !board.getPiece(2, toY) && !target) return true;
            if (dx == 1 && dy == 0 && !target) return true;
            if (dx == 1 && abs(dy) == 1 && target) return true;
            return false;
        }
        else { // Красные двигаются вниз
            if (fromX == 6 && toX == 4 && fromY == toY && !board.getPiece(5, toY) && !target) return true;
            if (dx == -1 && dy == 0 && !target) return true;
            if (dx == -1 && abs(dy) == 1 && target) return true;
            return false;
        }

    case 'R': // Ладья
        if (dx != 0 && dy != 0) return false;
        {
            int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
            int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;
            int x = fromX + stepX;
            int y = fromY + stepY;
            while (x != toX || y != toY) {
                if (board.getPiece(x, y)) return false;
                x += stepX;
                y += stepY;
            }
            return true;
        }

    case 'N': // Конь
        return (abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2);

    case 'B': // Слон
        if (abs(dx) != abs(dy)) return false;
        {
            int stepX = (dx > 0) ? 1 : -1;
            int stepY = (dy > 0) ? 1 : -1;
            int x = fromX + stepX;
            int y = fromY + stepY;
            while (x != toX || y != toY) {
                if (board.getPiece(x, y)) return false;
                x += stepX;
                y += stepY;
            }
            return true;
        }

    case 'Q': // Ферзь
        if (dx == 0 || dy == 0 || abs(dx) == abs(dy)) {
            int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
            int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;
            int x = fromX + stepX;
            int y = fromY + stepY;
            while (x != toX || y != toY) {
                if (board.getPiece(x, y)) return false;
                x += stepX;
                y += stepY;
            }
            return true;
        }
        return false;

    case 'K': // Король
        return abs(dx) <= 1 && abs(dy) <= 1;

    default:
        return false;
    }
}