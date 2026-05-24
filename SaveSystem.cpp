#include "SaveSystem.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>

const std::string SaveSystem::SAVE_FILE = "savegame.dat";

bool SaveSystem::saveGame(const Player& player, int currentNode) {
    std::ofstream file(SAVE_FILE);
    if (!file.is_open()) {
        colorPrintLn("  Error: Could not save game!", Color::RED);
        return false;
    }
    file << currentNode << "\n";
    file << player.serialize() << "\n";
    file.close();
    colorPrintLn("  Game saved successfully!", Color::GREEN);
    return true;
}

bool SaveSystem::loadGame(Player& player, int& currentNode) {
    std::ifstream file(SAVE_FILE);
    if (!file.is_open()) {
        colorPrintLn("  No save file found!", Color::RED);
        return false;
    }
    std::string line;
    if (!std::getline(file, line)) { file.close(); return false; }
    currentNode = std::stoi(line);

    if (!std::getline(file, line)) { file.close(); return false; }
    player.deserialize(line);

    file.close();
    colorPrintLn("  Game loaded successfully!", Color::GREEN);
    return true;
}

bool SaveSystem::saveFileExists() {
    std::ifstream file(SAVE_FILE);
    return file.good();
}

void SaveSystem::deleteSave() {
    std::remove(SAVE_FILE.c_str());
}
