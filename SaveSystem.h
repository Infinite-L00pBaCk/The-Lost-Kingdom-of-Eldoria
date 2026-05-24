#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include "Player.h"
#include <string>

class SaveSystem {
private:
    static const std::string SAVE_FILE;

public:
    static bool saveGame(const Player& player, int currentNode);
    static bool loadGame(Player& player, int& currentNode);
    static bool saveFileExists();
    static void deleteSave();
};

#endif
