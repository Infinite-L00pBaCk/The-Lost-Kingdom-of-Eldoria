/******************************************************************************
 *  The Lost Kingdom of Eldoria
 *  A Text-Based Adventure Game in C++
 *
 *  Developed for: Pinnacle Labs Internship Task
 *  Features: Branching storyline, turn-based combat, inventory system,
 *            character classes, karma system, save/load, multiple endings.
 *
 *  Compile: g++ -o eldoria main.cpp Game.cpp Player.cpp Story.cpp
 *           Combat.cpp Utils.cpp SaveSystem.cpp -std=c++17
 *  Run:     ./eldoria  (Linux/Mac)  or  eldoria.exe  (Windows)
 ******************************************************************************/

#include "Game.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // Enable UTF-8 output for Windows console (for special characters)
    SetConsoleOutputCP(65001);
#endif

    Game game;
    game.run();

    return 0;
}
