#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "ai.h"
#include "interface.h" // Добавляем интерфейс

class Game {
private:
    Board board;
    AI redAI;
    bool blueTurn;
    Interface ui; // Экземпляр интерфейса
public:
    Game();
    void play();
};

#endif