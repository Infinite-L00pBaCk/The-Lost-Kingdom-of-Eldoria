#include "Combat.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

// ─── Enemy Factory Functions ────────────────────────────────────────────────

Enemy createForestWolf() {
    return Enemy("Forest Wolf", 45, 9, 2, 25, 10,
                 "The wolf snarls, baring its fangs!");
}

Enemy createGoblinScout() {
    return Enemy("Goblin Scout", 55, 11, 3, 35, 20,
                 "The goblin cackles and waves a rusty dagger!");
}

Enemy createSkeletonWarrior() {
    return Enemy("Skeleton Warrior", 80, 14, 6, 55, 30,
                 "Bones rattle as the skeleton raises its ancient sword!");
}

Enemy createDarkMage() {
    return Enemy("Dark Mage", 65, 20, 4, 70, 45,
                 "Dark energy crackles between the mage's fingers!");
}

Enemy createBanditLeader() {
    return Enemy("Bandit Leader", 90, 16, 7, 60, 50,
                 "\"Your gold or your life!\" the bandit sneers.");
}

Enemy createShadowDragon() {
    return Enemy("Shadow Dragon", 200, 25, 12, 200, 100,
                 "The dragon's eyes glow crimson as shadows swirl around it!");
}

// ─── Display ────────────────────────────────────────────────────────────────

void displayEnemyHealth(const Enemy& enemy) {
    colorPrint("  " + enemy.name + " HP: ", Color::RED);
    int barLen = 20;
    int filled = (enemy.health * barLen) / enemy.maxHealth;
    setColor(Color::RED);
    std::cout << "[";
    for (int i = 0; i < barLen; i++) {
        std::cout << (i < filled ? "█" : " ");
    }
    std::cout << "] " << enemy.health << "/" << enemy.maxHealth << "\n";
    resetColor();
}

// ─── Combat System ──────────────────────────────────────────────────────────

bool runCombat(Player& player, Enemy enemy) {
    clearScreen();
    printSeparator('=', 60, Color::RED);
    colorPrintLn("                   ⚔  COMBAT ENCOUNTER  ⚔", Color::RED);
    printSeparator('=', 60, Color::RED);
    std::cout << "\n";
    typewriterColor("  A " + enemy.name + " appears!", Color::YELLOW, 30);
    if (!enemy.taunt.empty()) {
        typewriterColor("  " + enemy.taunt, Color::DARK_GRAY, 20);
    }
    std::cout << "\n";

    bool playerDefending = false;
    int turnCount = 0;

    while (player.isAlive() && enemy.isAlive()) {
        turnCount++;

        // Display status
        printSeparator('-', 50, Color::DARK_CYAN);
        colorPrintLn("  Turn " + std::to_string(turnCount), Color::CYAN);
        displayEnemyHealth(enemy);

        colorPrint("  Your HP: ", Color::GREEN);
        int barLen = 20;
        int filled = (player.getHealth() * barLen) / player.getMaxHealth();
        Color hpColor = (player.getHealth() > player.getMaxHealth() / 2) ? Color::GREEN :
                        (player.getHealth() > player.getMaxHealth() / 4) ? Color::YELLOW : Color::RED;
        setColor(hpColor);
        std::cout << "[";
        for (int i = 0; i < barLen; i++) {
            std::cout << (i < filled ? "█" : " ");
        }
        std::cout << "] " << player.getHealth() << "/" << player.getMaxHealth() << "\n";
        resetColor();

        // Player's turn
        std::cout << "\n";
        colorPrintLn("  What will you do?", Color::WHITE);
        colorPrintLn("    [1] Attack", Color::RED);
        colorPrintLn("    [2] Defend", Color::BLUE);
        colorPrintLn("    [3] Use Item", Color::GREEN);
        colorPrintLn("    [4] Flee", Color::YELLOW);

        int choice = getValidInput(1, 4);
        playerDefending = false;

        switch (choice) {
            case 1: { // Attack
                int dmg = std::max(1, player.getAttack() - enemy.defense + randomInt(-2, 2));
                // Mage bonus: chance of critical
                if (player.getClass() == CharacterClass::MAGE && randomInt(1, 100) <= 25) {
                    dmg *= 2;
                    colorPrintLn("  ✦ CRITICAL HIT! Your spell surges with power!", Color::MAGENTA);
                }
                enemy.health = std::max(0, enemy.health - dmg);
                colorPrintLn("  You strike the " + enemy.name + " for " + std::to_string(dmg) + " damage!", Color::GREEN);
                break;
            }
            case 2: // Defend
                playerDefending = true;
                colorPrintLn("  You brace yourself, raising your guard!", Color::BLUE);
                break;
            case 3: { // Use Item
                if (player.getInventory().empty()) {
                    colorPrintLn("  You have no items!", Color::RED);
                    continue; // Redo turn
                }
                player.displayInventory();
                colorPrintLn("  [0] Cancel", Color::DARK_GRAY);
                int itemChoice = getValidInput(0, static_cast<int>(player.getInventory().size()));
                if (itemChoice == 0) continue;
                player.useItem(itemChoice - 1);
                break;
            }
            case 4: { // Flee
                int fleeChance = 50;
                if (player.getClass() == CharacterClass::ROGUE) fleeChance = 75;
                if (randomInt(1, 100) <= fleeChance) {
                    colorPrintLn("  You successfully fled from combat!", Color::YELLOW);
                    sleepMs(1000);
                    return false; // Not a win, but not dead
                } else {
                    colorPrintLn("  You failed to escape!", Color::RED);
                }
                break;
            }
        }

        if (!enemy.isAlive()) break;

        // Enemy's turn
        sleepMs(500);
        int enemyDmg = std::max(1, enemy.attack - player.getDefense() / 3 + randomInt(-2, 2));
        if (playerDefending) {
            enemyDmg /= 2;
            colorPrintLn("  Your defense absorbs some of the blow!", Color::BLUE);
        }
        int prevHP = player.getHealth();
        player.takeDamage(enemyDmg);
        int actualDmg = prevHP - player.getHealth();
        colorPrintLn("  The " + enemy.name + " attacks you for " + std::to_string(actualDmg) + " damage!", Color::RED);
        sleepMs(300);
    }

    if (!player.isAlive()) {
        std::cout << "\n";
        colorPrintLn("  ╔══════════════════════════════════════╗", Color::RED);
        colorPrintLn("  ║         YOU HAVE BEEN DEFEATED       ║", Color::RED);
        colorPrintLn("  ╚══════════════════════════════════════╝", Color::RED);
        sleepMs(1500);
        return false;
    }

    // Victory!
    std::cout << "\n";
    colorPrintLn("  ╔══════════════════════════════════════╗", Color::GREEN);
    colorPrintLn("  ║            ★ VICTORY! ★              ║", Color::GREEN);
    colorPrintLn("  ╚══════════════════════════════════════╝", Color::GREEN);
    colorPrintLn("  The " + enemy.name + " has been defeated!", Color::GREEN);
    colorPrintLn("  + " + std::to_string(enemy.expReward) + " XP", Color::CYAN);
    colorPrintLn("  + " + std::to_string(enemy.goldReward) + " Gold", Color::YELLOW);

    player.addExperience(enemy.expReward);
    player.addGold(enemy.goldReward);
    sleepMs(1000);
    pressEnterToContinue();
    return true;
}
