#include "ChessBoard.h"

int main() {
    setlocale(LC_ALL, "russian");

    ChessBoard board;
    string from, to;

    while (true) {
        board.displayBoard();
        cout << "Ход игрока " << board.getCurrentPlayer() << ". Введите ход (например, e2 e4): ";
        cin >> from >> to;

        if (board.movePiece(from, to)) {
            board.switchPlayer(); 
        }
    }

    return 0;
}

