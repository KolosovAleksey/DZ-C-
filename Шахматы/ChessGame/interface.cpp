#include "interface.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

void Interface::displayBoard(const Board& board) const {
    clearScreen();

    auto getSymbol = [](char symbol, bool isBlue) -> const char* {
        if (isBlue) {
            switch (symbol) {
            case 'P': return u8"\u2659"; // Синие фигуры
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
            case 'P': return u8"\u265F"; // Красные фигуры
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
    const char* BORDER_FG = "\033[33m"; // Желтый для рамки

    cout << BORDER_FG << "\n   === Chess Game ===   \n" << RESET;
    cout << "    a   b   c   d   e   f   g   h  \n";
    cout << BORDER_FG << "  +---+---+---+---+---+---+---+---+\n" << RESET;

    for (int i = 7; i >= 0; i--) {
        cout << BORDER_FG << (i + 1) << " " << RESET << "|";
        for (int j = 0; j < 8; j++) {
            bool isWhiteSquare = (i + j) % 2 == 0;
            cout << (isWhiteSquare ? WHITE_BG : BLACK_BG);
            Piece* piece = board.getPiece(i, j);
            if (piece) {
                bool isBlue = piece->isBluePiece();
                cout << (isBlue ? BLUE_FG : RED_FG);
                cout << " " << getSymbol(piece->getSymbol(), isBlue) << " ";
            }
            else {
                cout << "   ";
            }
            cout << RESET << "|";
        }
        cout << BORDER_FG << " " << (i + 1) << RESET << "\n";
        if (i > 0) {
            cout << BORDER_FG << "  +---+---+---+---+---+---+---+---+\n" << RESET;
        }
    }
    cout << BORDER_FG << "  +---+---+---+---+---+---+---+---+\n" << RESET;
    cout << "    a   b   c   d   e   f   g   h  \n";
}

void Interface::showTurn(bool isBlueTurn) const {
    cout << (isBlueTurn ? "\033[34mBlue's turn\033[0m" : "\033[31mRed's turn (AI)\033[0m") << "\n";
}

void Interface::showMove(const string& move, bool isAI) const {
    if (isAI) {
        cout << "\033[31mAI is thinking...\033[0m";
        this_thread::sleep_for(chrono::milliseconds(1000)); // Задержка для эффекта
        cout << "\r\033[31mAI moves: " << move << "\033[0m\n";
    }
    else {
        cout << "\033[34mPlayer moves: " << move << "\033[0m\n";
    }
}

void Interface::showCheck(bool isBlue) const {
    cout << (isBlue ? "\033[34mBlue king is in check!\033[0m" : "\033[31mRed king is in check!\033[0m") << "\n";
}

void Interface::showGameResult(bool blueCheckmate, bool redCheckmate, bool stalemate) const {
    if (blueCheckmate) {
        cout << "\033[31mCheckmate! Red wins!\033[0m\n";
    }
    else if (redCheckmate) {
        cout << "\033[34mCheckmate! Blue wins!\033[0m\n";
    }
    else if (stalemate) {
        cout << "\033[33mStalemate! It's a draw!\033[0m\n";
    }
    cout << "Game ended. Press Enter to exit.\n";
}

string Interface::getPlayerMove() const {
    string move;
    cout << "Enter your move (e.g., e2e4): ";
    cin >> move;
    return move;
}

void Interface::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}