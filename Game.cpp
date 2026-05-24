#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

Game::Game() : state(GameState::MAIN_MENU), currentNode(1), isRunning(true) {}

void Game::run() {
    while (isRunning) {
        switch (state) {
            case GameState::MAIN_MENU:        mainMenu(); break;
            case GameState::CHARACTER_CREATION: characterCreation(); break;
            case GameState::PLAYING:          processStoryNode(); break;
            case GameState::INVENTORY_MENU:   inventoryMenu(); break;
            case GameState::GAME_OVER:        gameOverScreen(); isRunning = false; break;
            case GameState::VICTORY:          isRunning = false; break;
        }
    }
    std::cout << "\n";
    colorPrintLn("  Thank you for playing The Lost Kingdom of Eldoria!", Color::CYAN);
    colorPrintLn("  Developed for Pinnacle Labs Internship", Color::DARK_GRAY);
    std::cout << "\n";
}

void Game::mainMenu() {
    clearScreen();
    printBanner();

    std::vector<std::string> options;
    options.push_back("New Game");
    if (SaveSystem::saveFileExists()) {
        options.push_back("Continue (Load Save)");
    }
    options.push_back("About");
    options.push_back("Quit");

    int choice = displayMenu("MAIN MENU", options);

    if (choice == 1) {
        // New Game
        if (SaveSystem::saveFileExists()) {
            if (getYesNo("Starting a new game will overwrite your save. Continue?")) {
                SaveSystem::deleteSave();
                state = GameState::CHARACTER_CREATION;
            }
        } else {
            state = GameState::CHARACTER_CREATION;
        }
    } else if (choice == 2 && SaveSystem::saveFileExists()) {
        // Load Game
        if (SaveSystem::loadGame(player, currentNode)) {
            state = GameState::PLAYING;
        }
        pressEnterToContinue();
    } else if ((choice == 2 && !SaveSystem::saveFileExists()) ||
               (choice == 3 && SaveSystem::saveFileExists())) {
        // About
        clearScreen();
        printBoxedTitle("ABOUT", Color::CYAN);
        std::cout << "\n";
        colorPrintLn("  The Lost Kingdom of Eldoria", Color::YELLOW);
        colorPrintLn("  A Text-Based Adventure Game in C++", Color::WHITE);
        std::cout << "\n";
        colorPrintLn("  Features:", Color::CYAN);
        colorPrintLn("  - Branching storyline with 25+ story nodes", Color::WHITE);
        colorPrintLn("  - 5 unique endings based on your choices", Color::WHITE);
        colorPrintLn("  - Turn-based combat system", Color::WHITE);
        colorPrintLn("  - Inventory and item management", Color::WHITE);
        colorPrintLn("  - Character classes: Warrior, Mage, Rogue", Color::WHITE);
        colorPrintLn("  - Karma system tracking moral choices", Color::WHITE);
        colorPrintLn("  - Save/Load game progress", Color::WHITE);
        std::cout << "\n";
        colorPrintLn("  Developed for Pinnacle Labs Internship Task", Color::GREEN);
        colorPrintLn("  Built with C++17", Color::DARK_GRAY);
        pressEnterToContinue();
    } else {
        // Quit
        isRunning = false;
    }
}

void Game::characterCreation() {
    clearScreen();
    printBoxedTitle("CHARACTER CREATION", Color::YELLOW);
    std::cout << "\n";
    typewriterColor("  Before your adventure begins, tell us about yourself...", Color::CYAN, 30);
    std::cout << "\n";

    // Name
    player.setName(getStringInput("Enter your name, adventurer"));

    // Class selection
    std::cout << "\n";
    colorPrintLn("  Choose your class:\n", Color::YELLOW);

    colorPrintLn("  [1] WARRIOR", Color::RED);
    colorPrintLn("      HP: 150 | ATK: 12 | DEF: 8", Color::DARK_GRAY);
    colorPrintLn("      A stalwart fighter with high health and defense.\n", Color::DARK_GRAY);

    colorPrintLn("  [2] MAGE", Color::MAGENTA);
    colorPrintLn("      HP: 90  | ATK: 18 | DEF: 4", Color::DARK_GRAY);
    colorPrintLn("      Powerful attacks with 25% critical hit chance.\n", Color::DARK_GRAY);

    colorPrintLn("  [3] ROGUE", Color::GREEN);
    colorPrintLn("      HP: 110 | ATK: 14 | DEF: 6 | +50 Gold", Color::DARK_GRAY);
    colorPrintLn("      Balanced stats with bonus gold and 75% flee chance.\n", Color::DARK_GRAY);

    int classChoice = getValidInput(1, 3);
    switch (classChoice) {
        case 1: player.setClass(CharacterClass::WARRIOR); break;
        case 2: player.setClass(CharacterClass::MAGE);    break;
        case 3: player.setClass(CharacterClass::ROGUE);   break;
    }

    clearScreen();
    colorPrintLn("\n  Character created successfully!\n", Color::GREEN);
    player.displayStats();
    pressEnterToContinue();

    currentNode = 1;
    state = GameState::PLAYING;
}

void Game::processStoryNode() {
    if (!story.hasNode(currentNode)) {
        colorPrintLn("  Error: Story node " + std::to_string(currentNode) + " not found!", Color::RED);
        state = GameState::GAME_OVER;
        return;
    }

    const StoryNode& node = story.getNode(currentNode);

    clearScreen();
    printSeparator('=', 60, Color::DARK_CYAN);
    colorPrintLn("  " + node.title, Color::YELLOW);
    printSeparator('=', 60, Color::DARK_CYAN);
    std::cout << "\n";

    // Display narrative with typewriter effect
    typewriterColor(node.narrative, Color::WHITE, 15);

    // Apply healing if any
    if (node.healAmount > 0) {
        std::cout << "\n";
        if (node.healAmount >= 999) {
            player.fullHeal();
            colorPrintLn("  ✦ Your health has been fully restored!", Color::GREEN);
        } else {
            player.heal(node.healAmount);
            colorPrintLn("  ✦ You recovered " + std::to_string(node.healAmount) + " HP!", Color::GREEN);
        }
    }

    // Give item reward
    if (node.hasItemReward) {
        std::cout << "\n";
        Item reward = node.itemReward;
        // Apply non-consumable item effects immediately
        if (!reward.isConsumable && (reward.attackBoost > 0 || reward.defenseBoost > 0)) {
            if (reward.attackBoost > 0) player.addAttack(reward.attackBoost);
            if (reward.defenseBoost > 0) player.addDefense(reward.defenseBoost);
        }
        player.addItem(reward);
    }

    // Handle combat
    if (node.hasCombat) {
        std::cout << "\n";
        pressEnterToContinue();
        handleCombat(node.enemyType);

        if (!player.isAlive()) {
            // Player died — show death ending
            currentNode = 34;
            state = GameState::PLAYING;
            return;
        }
    }

    // Check if this is an ending
    if (node.isEnding) {
        showEnding(node);
        return;
    }

    // Auto-save at certain nodes
    if (currentNode == 13 || currentNode == 20 || currentNode == 25) {
        std::cout << "\n";
        colorPrintLn("  [Auto-saving...]", Color::DARK_GRAY);
        SaveSystem::saveGame(player, currentNode);
    }

    // Display choices
    if (node.choices.empty()) {
        state = GameState::GAME_OVER;
        return;
    }

    std::cout << "\n";
    printSeparator('-', 50, Color::DARK_GRAY);
    colorPrintLn("  What do you do?\n", Color::CYAN);

    std::vector<int> validChoices;
    int displayNum = 1;
    for (size_t i = 0; i < node.choices.size(); i++) {
        const Choice& c = node.choices[i];
        bool available = true;

        if (!c.requiredItem.empty() && !player.hasItem(c.requiredItem)) {
            available = false;
        }

        if (available) {
            colorPrint("    [" + std::to_string(displayNum) + "] ", Color::GREEN);
            colorPrintLn(c.text, Color::WHITE);
            validChoices.push_back(static_cast<int>(i));
            displayNum++;
        } else {
            colorPrint("    [X] ", Color::DARK_GRAY);
            colorPrintLn(c.text + " (Requires: " + c.requiredItem + ")", Color::DARK_GRAY);
        }
    }

    // Extra options
    colorPrint("\n    [" + std::to_string(displayNum) + "] ", Color::YELLOW);
    colorPrintLn("View Stats & Inventory", Color::YELLOW);
    int saveOption = displayNum + 1;
    colorPrint("    [" + std::to_string(saveOption) + "] ", Color::DARK_CYAN);
    colorPrintLn("Save Game", Color::DARK_CYAN);

    int maxChoice = saveOption;
    int input = getValidInput(1, maxChoice);

    if (input == displayNum) {
        // Stats
        player.displayStats();
        player.displayInventory();
        pressEnterToContinue();
        return; // Re-display same node
    } else if (input == saveOption) {
        SaveSystem::saveGame(player, currentNode);
        pressEnterToContinue();
        return;
    }

    // Process story choice
    int choiceIndex = validChoices[input - 1];
    const Choice& chosen = node.choices[choiceIndex];

    // Apply karma
    if (chosen.karmaChange != 0) {
        player.addKarma(chosen.karmaChange);
        if (chosen.karmaChange > 0) {
            colorPrintLn("  [Karma +" + std::to_string(chosen.karmaChange) + "]", Color::GREEN);
        } else {
            colorPrintLn("  [Karma " + std::to_string(chosen.karmaChange) + "]", Color::RED);
        }
        sleepMs(500);
    }

    // Special: node 25 (throne room) — check for secret ending
    if (currentNode == 25 && chosen.nextNode == 31) {
        int ending = determineEnding();
        currentNode = ending;
    } else {
        currentNode = chosen.nextNode;
    }
}

void Game::handleCombat(int enemyType) {
    Enemy enemy;
    switch (enemyType) {
        case 1: enemy = createForestWolf(); break;
        case 2: enemy = createGoblinScout(); break;
        case 3: enemy = createSkeletonWarrior(); break;
        case 4: enemy = createDarkMage(); break;
        case 5: enemy = createBanditLeader(); break;
        case 6: {
            enemy = createShadowDragon();
            // If player has Light Amulet, dragon is weakened
            if (player.hasItem("Light Amulet")) {
                enemy.health -= 50;
                enemy.maxHealth -= 50;
                enemy.attack -= 5;
                colorPrintLn("  ✦ Your Light Amulet glows! The dragon's shadow armor weakens!", Color::YELLOW);
                sleepMs(1000);
            }
            // If player has Crystal of Light, further weaken
            if (player.hasItem("Crystal of Light")) {
                enemy.health -= 30;
                enemy.maxHealth -= 30;
                enemy.defense -= 4;
                colorPrintLn("  ✦ The Crystal of Light blazes! The dragon recoils!", Color::YELLOW);
                sleepMs(1000);
            }
            break;
        }
        default: enemy = createForestWolf(); break;
    }

    bool won = runCombat(player, enemy);
    if (!won && !player.isAlive()) {
        // Player died
        return;
    }
}

int Game::determineEnding() {
    // Secret ending: high karma + both key artifacts
    if (player.getKarma() >= 10 &&
        player.hasItem("Crystal of Light") &&
        player.hasItem("Light Amulet")) {
        return 33; // Ascended ending
    }
    return 31; // Regular good ending
}

void Game::showEnding(const StoryNode& node) {
    clearScreen();
    std::cout << "\n\n";
    printSeparator('*', 60, Color::YELLOW);
    colorPrintLn("", Color::WHITE);

    // Color based on ending type
    Color endColor = Color::WHITE;
    if (node.id == 30) endColor = Color::RED;        // Dark
    else if (node.id == 31) endColor = Color::GREEN;  // Hero
    else if (node.id == 32) endColor = Color::CYAN;   // Guardian
    else if (node.id == 33) endColor = Color::YELLOW;  // Ascended
    else if (node.id == 34) endColor = Color::DARK_GRAY; // Death

    typewriterColor(node.narrative, endColor, 35);

    std::cout << "\n\n";
    printSeparator('*', 60, Color::YELLOW);
    colorPrintLn("  " + node.endingTitle, Color::YELLOW);
    printSeparator('*', 60, Color::YELLOW);

    // Final stats
    std::cout << "\n";
    colorPrintLn("  ═══ FINAL STATS ═══", Color::CYAN);
    player.displayStats();

    // Delete save on ending
    SaveSystem::deleteSave();

    std::cout << "\n";
    colorPrintLn("  Congratulations on completing The Lost Kingdom of Eldoria!", Color::GREEN);
    colorPrintLn("  Try again for a different ending!\n", Color::CYAN);
    pressEnterToContinue();
    state = GameState::VICTORY;
}

void Game::gameOverScreen() {
    clearScreen();
    std::cout << "\n\n";
    setColor(Color::RED);
    std::cout << R"(
     ██████╗  █████╗ ███╗   ███╗███████╗
    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝
    ██║  ███╗███████║██╔████╔██║█████╗
    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝
    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗
     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝

     ██████╗ ██╗   ██╗███████╗██████╗
    ██╔═══██╗██║   ██║██╔════╝██╔══██╗
    ██║   ██║██║   ██║█████╗  ██████╔╝
    ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗
    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║
     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝
    )" << "\n";
    resetColor();

    colorPrintLn("  Your adventure has come to an end...", Color::DARK_GRAY);
    colorPrintLn("  But every ending is a new beginning.", Color::CYAN);
    std::cout << "\n";
    pressEnterToContinue();
}

void Game::inventoryMenu() {
    // This is called inline, not as a separate state in current design
    player.displayInventory();
    pressEnterToContinue();
    state = GameState::PLAYING;
}
