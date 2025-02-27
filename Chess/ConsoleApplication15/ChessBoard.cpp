#include "ChessBoard.h"

ChessBoard::ChessBoard() : currentPlayer("white") {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
    initializeBoard();
}

ChessBoard::~ChessBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
}

void ChessBoard::initializeBoard() {
    board[0][0] = new Rook("black");
    board[0][1] = new Knight("black");
    board[0][2] = new Bishop("black");
    board[0][3] = new Queen("black");
    board[0][4] = new King("black");
    board[0][5] = new Bishop("black");
    board[0][6] = new Knight("black");
    board[0][7] = new Rook("black");

    for (int i = 0; i < 8; ++i) {
        board[1][i] = new Pawn("black");
    }

    for (int i = 0; i < 8; ++i) {
        board[6][i] = new Pawn("white");
    }

    board[7][0] = new Rook("white");
    board[7][1] = new Knight("white");
    board[7][2] = new Bishop("white");
    board[7][3] = new Queen("white");
    board[7][4] = new King("white");
    board[7][5] = new Bishop("white");
    board[7][6] = new Knight("white");
    board[7][7] = new Rook("white");
}

void ChessBoard::displayBoard() const {
    cout << "     ";
    for (int i = 0; i < 8; ++i) {
        cout << "  " << char('a' + i) << "   ";
    }
    cout << endl;

    cout << "   ";
    for (int i = 0; i < 8; ++i) {
        cout << "+-----";
    }
    cout << "+" << endl;

    for (int i = 0; i < 8; ++i) {
        cout << " " << 8 - i << " ";
        for (int j = 0; j < 8; ++j) {
            cout << "|";

            string bgColor = ((i + j) % 2 == 0) ? "\033[47m" : "\033[40m";
            cout << bgColor;

            if (board[i][j] == nullptr) {
                cout << "     ";
            }
            else {
                string pieceName = board[i][j]->getName();
                string color = board[i][j]->getColor();
                string symbol = pieceName.substr(0, 1);

                string textColor = (color == "black") ? "\033[1;31m" : "\033[1;34m";
                cout << "  " << textColor << symbol << "\033[0m" << bgColor << "  ";
            }
            cout << "\033[0m";
        }
        cout << "| " << 8 - i << endl;

        cout << "   ";
        for (int j = 0; j < 8; ++j) {
            cout << "+-----";
        }
        cout << "+" << endl;
    }

    cout << "     ";
    for (int i = 0; i < 8; ++i) {
        cout << "  " << char('a' + i) << "   ";
    }
    cout << endl;
}

bool ChessBoard::movePiece(const string& from, const string& to) {
    int fromX = 8 - (from[1] - '0');
    int fromY = from[0] - 'a';
    int toX = 8 - (to[1] - '0');
    int toY = to[0] - 'a';

    if (fromX < 0 || fromX >= 8 || fromY < 0 || fromY >= 8 ||
        toX < 0 || toX >= 8 || toY < 0 || toY >= 8) {
        cout << "Некорректные координаты!" << endl;
        return false;
    }

    ChessPiece* piece = board[fromX][fromY];

    if (piece == nullptr) {
        cout << "На начальной клетке нет фигуры!" << endl;
        return false;
    }

    if (piece->getColor() != currentPlayer) {
        cout << "Это не ваша фигура!" << endl;
        return false;
    }

    string possibleMoves = piece->getPossibleMoves(from);
    if (possibleMoves.find(to) == string::npos) {
        cout << "Недопустимый ход для этой фигуры!" << endl;
        return false;
    }

    delete board[toX][toY];
    board[toX][toY] = piece;
    board[fromX][fromY] = nullptr;

    return true;
}

string ChessBoard::getCurrentPlayer() const {
    return currentPlayer;
}

void ChessBoard::switchPlayer() {
    currentPlayer = (currentPlayer == "white") ? "black" : "white";
}