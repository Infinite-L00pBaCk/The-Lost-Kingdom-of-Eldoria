#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Story.h"
#include "Combat.h"
#include "SaveSystem.h"

enum class GameState {
    MAIN_MENU,
    CHARACTER_CREATION,
    PLAYING,
    INVENTORY_MENU,
    GAME_OVER,
    VICTORY
};

class Game {
private:
    Player player;
    Story story;
    GameState state;
    int currentNode;
    bool isRunning;

    void mainMenu();
    void characterCreation();
    void processStoryNode();
    void inventoryMenu();
    void showEnding(const StoryNode& node);
    void gameOverScreen();
    void handleCombat(int enemyType);
    int determineEnding();

public:
    Game();
    void run();
};

#endif
