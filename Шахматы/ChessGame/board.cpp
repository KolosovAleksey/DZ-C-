#include "board.h"
#include <iostream>

using namespace std;

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = nullptr;
        }
    }
}

Board::~Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete squares[i][j];
        }
    }
}

Board::Board(const Board& other) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (other.squares[i][j]) {
                squares[i][j] = new Piece(other.squares[i][j]->getSymbol(), other.squares[i][j]->isBluePiece());
            }
            else {
                squares[i][j] = nullptr;
            }
        }
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                delete squares[i][j];
                if (other.squares[i][j]) {
                    squares[i][j] = new Piece(other.squares[i][j]->getSymbol(), other.squares[i][j]->isBluePiece());
                }
                else {
                    squares[i][j] = nullptr;
                }
            }
        }
    }
    return *this;
}

void Board::initialize() {
    squares[0][0] = new Piece('R', true);
    squares[0][1] = new Piece('N', true);
    squares[0][2] = new Piece('B', true);
    squares[0][3] = new Piece('Q', true);
    squares[0][4] = new Piece('K', true);
    squares[0][5] = new Piece('B', true);
    squares[0][6] = new Piece('N', true);
    squares[0][7] = new Piece('R', true);
    for (int i = 0; i < 8; i++) {
        squares[1][i] = new Piece('P', true);
    }

    squares[7][0] = new Piece('R', false);
    squares[7][1] = new Piece('N', false);
    squares[7][2] = new Piece('B', false);
    squares[7][3] = new Piece('Q', false);
    squares[7][4] = new Piece('K', false);
    squares[7][5] = new Piece('B', false);
    squares[7][6] = new Piece('N', false);
    squares[7][7] = new Piece('R', false);
    for (int i = 0; i < 8; i++) {
        squares[6][i] = new Piece('P', false);
    }
}

void Board::display() const {
    auto getSymbol = [](char symbol, bool isBlue) -> const char* {
        if (isBlue) {
            switch (symbol) {
            case 'P': return u8"\u2659";
            case 'R': return u8"\u2656";
            case 'N': return u8"\u2658";
            case 'B': return u8"\u2657";
            case 'Q': return u8"\u2655";
            case 'K': return u8"\u2654";
            default: return " ";
            }
        }
        else {
            switch (symbol) {
            case 'P': return u8"\u265F";
            case 'R': return u8"\u265C";
            case 'N': return u8"\u265E";
            case 'B': return u8"\u265D";
            case 'Q': return u8"\u265B";
            case 'K': return u8"\u265A";
            default: return " ";
            }
        }
        };

    const char* RESET = "\033[0m";
    const char* BLACK_BG = "\033[40m";
    const char* WHITE_BG = "\033[47m";
    const char* BLUE_FG = "\033[34m";
    const char* RED_FG = "\033[31m";

    cout << "\n    a   b   c   d   e   f   g   h  \n";
    cout << "  +---+---+---+---+---+---+---+---+\n";

    for (int i = 7; i >= 0; i--) {
        cout << (i + 1) << " |";
        for (int j = 0; j < 8; j++) {
            bool isWhiteSquare = (i + j) % 2 == 0;
            cout << (isWhiteSquare ? WHITE_BG : BLACK_BG);
            if (squares[i][j]) {
                bool isBlue = squares[i][j]->isBluePiece();
                cout << (isBlue ? BLUE_FG : RED_FG);
                cout << " " << getSymbol(squares[i][j]->getSymbol(), isBlue) << " ";
            }
            else {
                cout << "   ";
            }
            cout << RESET << "|";
        }
        cout << " " << (i + 1) << "\n";
        if (i > 0) {
            cout << "  +---+---+---+---+---+---+---+---+\n";
        }
    }
    cout << "  +---+---+---+---+---+---+---+---+\n";
    cout << "    a   b   c   d   e   f   g   h  \n";
}

Piece* Board::getPiece(int x, int y) const {
    return (x >= 0 && x < 8 && y >= 0 && y < 8) ? squares[x][y] : nullptr;
}

bool Board::movePiece(int fromX, int fromY, int toX, int toY, bool isBlueTurn) {
    Piece* piece = getPiece(fromX, fromY);
    if (!piece || piece->isBluePiece() != isBlueTurn || !piece->isValidMove(fromX, fromY, toX, toY, *this)) {
        return false;
    }

    Piece* temp = squares[toX][toY];
    squares[toX][toY] = piece;
    squares[fromX][fromY] = nullptr;
    bool causesCheck = isKingInCheck(isBlueTurn);
    if (causesCheck) {
        squares[fromX][fromY] = piece;
        squares[toX][toY] = temp;
        return false;
    }

    delete temp;
    squares[toX][toY] = piece;
    squares[fromX][fromY] = nullptr;

    if (piece->getSymbol() == 'P') {
        if (isBlueTurn && toX == 7) {
            delete squares[toX][toY];
            squares[toX][toY] = new Piece('Q', true);
        }
        else if (!isBlueTurn && toX == 0) {
            delete squares[toX][toY];
            squares[toX][toY] = new Piece('Q', false);
        }
    }

    return true;
}

bool Board::isKingInCheck(bool isBlue) const {
    int kingX = -1, kingY = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = squares[i][j];
            if (p && p->getSymbol() == 'K' && p->isBluePiece() == isBlue) {
                kingX = i;
                kingY = j;
                break;
            }
        }
        if (kingX != -1) break;
    }
    if (kingX == -1) return false;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = squares[i][j];
            if (p && p->isBluePiece() != isBlue) {
                if (p->isValidMove(i, j, kingX, kingY, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::canMove(bool isBlue) {
    for (int fromX = 0; fromX < 8; fromX++) {
        for (int fromY = 0; fromY < 8; fromY++) {
            Piece* p = squares[fromX][fromY];
            if (p && p->isBluePiece() == isBlue) {
                for (int toX = 0; toX < 8; toX++) {
                    for (int toY = 0; toY < 8; toY++) {
                        if (movePiece(fromX, fromY, toX, toY, isBlue)) {
                            Piece* temp = squares[toX][toY];
                            squares[toX][toY] = getPiece(fromX, fromY);
                            squares[fromX][fromY] = p;
                            if (temp && temp->getSymbol() == 'Q' && ((isBlue && toX == 7) || (!isBlue && toX == 0))) {
                                delete temp;
                            }
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(bool isBlue) {
    return isKingInCheck(isBlue) && !canMove(isBlue);
}