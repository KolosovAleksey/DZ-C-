#include "ai.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

AI::AI(int depth) {
    srand(static_cast<unsigned>(time(nullptr)));
}

void AI::makeMove(Board& board) {
    struct Move {
        int fromX, fromY, toX, toY;
    };

    vector<Move> attackMoves;
    vector<Move> allMoves;

    // Собираем все возможные ходы
    for (int fromX = 0; fromX < 8; fromX++) {
        for (int fromY = 0; fromY < 8; fromY++) {
            Piece* p = board.getPiece(fromX, fromY);
            if (p && !p->isBluePiece()) { // Красные фигуры
                for (int toX = 0; toX < 8; toX++) {
                    for (int toY = 0; toY < 8; toY++) {
                        if (p->isValidMove(fromX, fromY, toX, toY, board)) {
                            Move move{ fromX, fromY, toX, toY };
                            if (board.getPiece(toX, toY) && board.getPiece(toX, toY)->isBluePiece()) {
                                attackMoves.push_back(move); // Атака
                            }
                            else {
                                allMoves.push_back(move); // Обычный ход
                            }
                        }
                    }
                }
            }
        }
    }

    Move bestMove;
    bool hasMove = false;

    if (!attackMoves.empty()) {
        int index = rand() % attackMoves.size();
        bestMove = attackMoves[index];
        hasMove = true;
    }
    else if (!allMoves.empty()) {
        int index = rand() % allMoves.size();
        bestMove = allMoves[index];
        hasMove = true;
    }

    if (hasMove) {
        board.movePiece(bestMove.fromX, bestMove.fromY, bestMove.toX, bestMove.toY, false);
        char fromCol = 'a' + bestMove.fromY;
        char toCol = 'a' + bestMove.toY;
        string moveStr = string(1, fromCol) + to_string(bestMove.fromX + 1) +
            string(1, toCol) + to_string(bestMove.toX + 1);
        cout << "\033[31mAI is thinking...\033[0m";
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "\r\033[31mAI moves: " << moveStr << "\033[0m\n";
    }
    else {
        cout << "\033[31mAI has no legal moves!\033[0m\n"; // Диагностика
    }
}