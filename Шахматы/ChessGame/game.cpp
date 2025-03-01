#include "game.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

Game::Game() : blueTurn(true), redAI(3) {
    board.initialize();
}

void Game::play() {
    while (true) {
        ui.displayBoard(board);

        if (blueTurn) {
            if (board.isKingInCheck(true)) {
                ui.showCheck(true);
            }

            if (board.isCheckmate(true)) {
                ui.showGameResult(true, false, false);
                break;
            }
            if (!board.isKingInCheck(true) && !board.canMove(true)) {
                ui.showGameResult(false, false, true);
                break;
            }

            ui.showTurn(true);
            string move = ui.getPlayerMove();

            if (move.length() != 4 || move[0] < 'a' || move[0] > 'h' || move[2] < 'a' || move[2] > 'h' ||
                move[1] < '1' || move[1] > '8' || move[3] < '1' || move[3] > '8') {
                cout << "\033[31mInvalid move format! Use, e.g., e2e4.\033[0m\n";
                this_thread::sleep_for(chrono::milliseconds(1000));
                continue;
            }

            int fromY = move[0] - 'a';
            int fromX = move[1] - '1';
            int toY = move[2] - 'a';
            int toX = move[3] - '1';

            if (board.movePiece(fromX, fromY, toX, toY, blueTurn)) {
                ui.showMove(move, false);
                blueTurn = false;
            }
            else {
                cout << "\033[31mInvalid move!\033[0m\n";
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
        }
        else {
            if (board.isKingInCheck(false)) {
                ui.showCheck(false);
            }

            if (board.isCheckmate(false)) {
                ui.showGameResult(false, true, false);
                break;
            }
            if (!board.isKingInCheck(false) && !board.canMove(false)) {
                ui.showGameResult(false, false, true);
                break;
            }

            ui.showTurn(false);
            redAI.makeMove(board); // ИИ напрямую изменяет доску
            blueTurn = true;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}