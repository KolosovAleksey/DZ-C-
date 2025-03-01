#ifndef INTERFACE_H
#define INTERFACE_H

#include "board.h"
#include <curses.h>
#include <string>

class Interface {
public:
    void displayBoard(const Board& board) const;           // Вывод доски
    void showTurn(bool isBlueTurn) const;                  // Показать чей ход
    void showMove(const std::string& move, bool isAI) const; // Показать сделанный ход
    void showCheck(bool isBlue) const;                     // Уведомление о шахе
    void showGameResult(bool blueCheckmate, bool redCheckmate, bool stalemate) const; // Результат игры
    std::string getPlayerMove() const;                     // Получить ход игрока
    void clearScreen() const;                              // Очистка экрана
};

#endif