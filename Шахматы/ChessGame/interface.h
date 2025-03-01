#ifndef INTERFACE_H
#define INTERFACE_H

#include "board.h"
#include <curses.h>
#include <string>

class Interface {
public:
    void displayBoard(const Board& board) const;           // ����� �����
    void showTurn(bool isBlueTurn) const;                  // �������� ��� ���
    void showMove(const std::string& move, bool isAI) const; // �������� ��������� ���
    void showCheck(bool isBlue) const;                     // ����������� � ����
    void showGameResult(bool blueCheckmate, bool redCheckmate, bool stalemate) const; // ��������� ����
    std::string getPlayerMove() const;                     // �������� ��� ������
    void clearScreen() const;                              // ������� ������
};

#endif