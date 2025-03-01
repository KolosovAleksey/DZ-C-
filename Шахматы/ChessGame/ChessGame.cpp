#include "game.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    Game chessGame;
    chessGame.play();
    return 0;
}