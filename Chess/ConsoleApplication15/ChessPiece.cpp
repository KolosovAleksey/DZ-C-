#include "ChessPiece.h"

ChessPiece::ChessPiece(const string& color, const string& name)
    : color(color), name(name) {}

ChessPiece::~ChessPiece() {}

string ChessPiece::getColor() const {
    return color;
}

string ChessPiece::getName() const {
    return name;
}

void ChessPiece::display() const {
    cout << color << " " << name << endl;
}

Pawn::Pawn(const string& color)
    : ChessPiece(color, "Pawn") {}

string Pawn::getPossibleMoves(const string& currentPosition) const {
    char x = currentPosition[0];
    char y = currentPosition[1];
    string moves;

    if (color == "white") {
        if (y < '8') moves += string(1, x) + string(1, char(y + 1)) + " ";
    }
    else {
        if (y > '1') moves += string(1, x) + string(1, char(y - 1)) + " ";
    }

    return moves;
}

Rook::Rook(const string& color)
    : ChessPiece(color, "Rook") {}

string Rook::getPossibleMoves(const string& currentPosition) const {
    char x = currentPosition[0];
    char y = currentPosition[1];
    string moves;

    for (char i = '1'; i <= '8'; ++i) {
        if (i != y) moves += string(1, x) + string(1, i) + " ";
    }

    for (char i = 'a'; i <= 'h'; ++i) {
        if (i != x) moves += string(1, i) + string(1, y) + " ";
    }

    return moves;
}

Knight::Knight(const string& color)
    : ChessPiece(color, "Knight") {}

string Knight::getPossibleMoves(const string& currentPosition) const {
    char x = currentPosition[0];
    char y = currentPosition[1];
    string moves;

    int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for (int i = 0; i < 8; ++i) {
        char newX = x + dx[i];
        char newY = y + dy[i];

        if (newX >= 'a' && newX <= 'h' && newY >= '1' && newY <= '8') {
            moves += string(1, newX) + string(1, newY) + " ";
        }
    }

    return moves;
}

Bishop::Bishop(const string& color)
    : ChessPiece(color, "Bishop") {}

string Bishop::getPossibleMoves(const string& currentPosition) const {
    char x = currentPosition[0];
    char y = currentPosition[1];
    string moves;

    for (char i = 'a'; i <= 'h'; ++i) {
        for (char j = '1'; j <= '8'; ++j) {
            if (abs(i - x) == abs(j - y) && (i != x || j != y)) {
                moves += string(1, i) + string(1, j) + " ";
            }
        }
    }

    return moves;
}

Queen::Queen(const string& color)
    : ChessPiece(color, "Queen") {}

string Queen::getPossibleMoves(const string& currentPosition) const {
    char x = currentPosition[0];
    char y = currentPosition[1];
    string moves;

    for (char i = 'a'; i <= 'h'; ++i) {
        for (char j = '1'; j <= '8'; ++j) {
            if ((i == x || j == y || abs(i - x) == abs(j - y)) && (i != x || j != y)) {
                moves += string(1, i) + string(1, j) + " ";
            }
        }
    }

    return moves;
}

King::King(const string& color)
    : ChessPiece(color, "King") {}

string King::getPossibleMoves(const string& currentPosition) const {
    char x = currentPosition[0];
    char y = currentPosition[1];
    string moves;

    for (char i = x - 1; i <= x + 1; ++i) {
        for (char j = y - 1; j <= y + 1; ++j) {
            if (i >= 'a' && i <= 'h' && j >= '1' && j <= '8' && (i != x || j != y)) {
                moves += string(1, i) + string(1, j) + " ";
            }
        }
    }

    return moves;
}