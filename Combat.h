#ifndef COMBAT_H
#define COMBAT_H

#include "Player.h"
#include <string>

struct Enemy {
    std::string name;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int expReward;
    int goldReward;
    std::string taunt;

    Enemy(const std::string& n = "", int hp = 50, int atk = 8, int def = 3,
          int xp = 30, int gld = 15, const std::string& t = "")
        : name(n), health(hp), maxHealth(hp), attack(atk), defense(def),
          expReward(xp), goldReward(gld), taunt(t) {}

    bool isAlive() const { return health > 0; }
};

// Pre-defined enemies
Enemy createForestWolf();
Enemy createGoblinScout();
Enemy createSkeletonWarrior();
Enemy createDarkMage();
Enemy createBanditLeader();
Enemy createShadowDragon(); // Boss

// Run a combat encounter; returns true if player wins
bool runCombat(Player& player, Enemy enemy);

// Display enemy health bar
void displayEnemyHealth(const Enemy& enemy);

#endif
