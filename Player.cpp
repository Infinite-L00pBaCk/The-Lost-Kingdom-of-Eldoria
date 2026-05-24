#include "Player.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Player::Player()
    : charClass(CharacterClass::WARRIOR),
      health(100), maxHealth(100), attack(10), defense(5),
      gold(0), level(1), experience(0), expToNextLevel(100), karma(0) {}

void Player::setName(const std::string& playerName) { name = playerName; }

void Player::setClass(CharacterClass cls) {
    charClass = cls;
    switch (cls) {
        case CharacterClass::WARRIOR:
            maxHealth = 150; health = 150; attack = 12; defense = 8;
            break;
        case CharacterClass::MAGE:
            maxHealth = 90; health = 90; attack = 18; defense = 4;
            break;
        case CharacterClass::ROGUE:
            maxHealth = 110; health = 110; attack = 14; defense = 6;
            gold = 50; // Rogues start with bonus gold
            break;
    }
}

std::string Player::getName() const { return name; }
CharacterClass Player::getClass() const { return charClass; }
std::string Player::getClassName() const {
    switch (charClass) {
        case CharacterClass::WARRIOR: return "Warrior";
        case CharacterClass::MAGE:    return "Mage";
        case CharacterClass::ROGUE:   return "Rogue";
    }
    return "Unknown";
}

int Player::getHealth() const { return health; }
int Player::getMaxHealth() const { return maxHealth; }
int Player::getAttack() const { return attack; }
int Player::getDefense() const { return defense; }
int Player::getGold() const { return gold; }
int Player::getLevel() const { return level; }
int Player::getExperience() const { return experience; }
int Player::getExpToNextLevel() const { return expToNextLevel; }
int Player::getKarma() const { return karma; }
const std::vector<Item>& Player::getInventory() const { return inventory; }

void Player::takeDamage(int amount) {
    int dmg = std::max(1, amount - defense / 3);
    health = std::max(0, health - dmg);
}

void Player::heal(int amount) {
    health = std::min(maxHealth, health + amount);
}

bool Player::isAlive() const { return health > 0; }

void Player::fullHeal() { health = maxHealth; }

void Player::addAttack(int amount) { attack += amount; }
void Player::addDefense(int amount) { defense += amount; }

void Player::addGold(int amount) { gold += amount; }

bool Player::spendGold(int amount) {
    if (gold >= amount) { gold -= amount; return true; }
    return false;
}

void Player::addExperience(int amount) {
    experience += amount;
    while (experience >= expToNextLevel) {
        experience -= expToNextLevel;
        level++;
        expToNextLevel = static_cast<int>(expToNextLevel * 1.5);
        maxHealth += 15;
        health = maxHealth;
        attack += 3;
        defense += 2;
        colorPrintLn("\n  *** LEVEL UP! You are now Level " + std::to_string(level) + "! ***", Color::YELLOW);
        colorPrintLn("  HP +" + std::to_string(15) + " | ATK +" + std::to_string(3) + " | DEF +" + std::to_string(2), Color::GREEN);
    }
}

void Player::addKarma(int amount) { karma += amount; }

std::string Player::getKarmaTitle() const {
    if (karma >= 20) return "Saint";
    if (karma >= 10) return "Hero";
    if (karma >= 3) return "Good";
    if (karma >= -2) return "Neutral";
    if (karma >= -9) return "Shady";
    if (karma >= -19) return "Villain";
    return "Dark Lord";
}

bool Player::addItem(const Item& item) {
    if (inventory.size() >= 15) {
        colorPrintLn("  Inventory is full! Cannot carry more items.", Color::RED);
        return false;
    }
    inventory.push_back(item);
    colorPrintLn("  + Acquired: " + item.name, Color::GREEN);
    return true;
}

bool Player::useItem(int index) {
    if (index < 0 || index >= static_cast<int>(inventory.size())) return false;
    Item& item = inventory[index];

    if (item.healAmount > 0) {
        heal(item.healAmount);
        colorPrintLn("  Used " + item.name + " — restored " + std::to_string(item.healAmount) + " HP!", Color::GREEN);
    }
    if (item.attackBoost > 0) {
        addAttack(item.attackBoost);
        colorPrintLn("  " + item.name + " boosted your Attack by " + std::to_string(item.attackBoost) + "!", Color::YELLOW);
    }
    if (item.defenseBoost > 0) {
        addDefense(item.defenseBoost);
        colorPrintLn("  " + item.name + " boosted your Defense by " + std::to_string(item.defenseBoost) + "!", Color::YELLOW);
    }
    if (item.isConsumable) {
        inventory.erase(inventory.begin() + index);
    }
    return true;
}

bool Player::removeItem(int index) {
    if (index < 0 || index >= static_cast<int>(inventory.size())) return false;
    if (inventory[index].isKeyItem) {
        colorPrintLn("  Cannot discard a key item!", Color::RED);
        return false;
    }
    inventory.erase(inventory.begin() + index);
    return true;
}

bool Player::hasItem(const std::string& itemName) const {
    for (const auto& item : inventory) {
        if (item.name == itemName) return true;
    }
    return false;
}

void Player::displayStats() const {
    std::cout << "\n";
    printSeparator('-', 50, Color::CYAN);
    colorPrint("  Name: ", Color::DARK_GRAY);
    colorPrintLn(name, Color::WHITE);
    colorPrint("  Class: ", Color::DARK_GRAY);
    colorPrintLn(getClassName(), Color::CYAN);
    colorPrint("  Level: ", Color::DARK_GRAY);
    colorPrintLn(std::to_string(level), Color::YELLOW);
    colorPrint("  XP: ", Color::DARK_GRAY);
    colorPrintLn(std::to_string(experience) + "/" + std::to_string(expToNextLevel), Color::WHITE);

    // Health bar
    colorPrint("  HP: ", Color::DARK_GRAY);
    int barLen = 20;
    int filled = (health * barLen) / maxHealth;
    Color hpColor = (health > maxHealth / 2) ? Color::GREEN :
                    (health > maxHealth / 4) ? Color::YELLOW : Color::RED;
    setColor(hpColor);
    std::cout << "[";
    for (int i = 0; i < barLen; i++) {
        std::cout << (i < filled ? "█" : " ");
    }
    std::cout << "] " << health << "/" << maxHealth << "\n";
    resetColor();

    colorPrint("  ATK: ", Color::DARK_GRAY);
    colorPrintLn(std::to_string(attack), Color::RED);
    colorPrint("  DEF: ", Color::DARK_GRAY);
    colorPrintLn(std::to_string(defense), Color::BLUE);
    colorPrint("  Gold: ", Color::DARK_GRAY);
    colorPrintLn(std::to_string(gold), Color::YELLOW);
    colorPrint("  Karma: ", Color::DARK_GRAY);
    Color karmaColor = karma >= 0 ? Color::GREEN : Color::RED;
    colorPrintLn(std::to_string(karma) + " (" + getKarmaTitle() + ")", karmaColor);
    printSeparator('-', 50, Color::CYAN);
}

void Player::displayInventory() const {
    std::cout << "\n";
    printBoxedTitle("INVENTORY", Color::YELLOW);
    if (inventory.empty()) {
        colorPrintLn("  (empty)", Color::DARK_GRAY);
        return;
    }
    for (size_t i = 0; i < inventory.size(); i++) {
        const Item& item = inventory[i];
        colorPrint("  [" + std::to_string(i + 1) + "] ", Color::GREEN);
        colorPrint(item.name, item.isKeyItem ? Color::MAGENTA : Color::WHITE);
        colorPrintLn(" - " + item.description, Color::DARK_GRAY);
    }
    colorPrintLn("  (" + std::to_string(inventory.size()) + "/15 slots used)", Color::DARK_GRAY);
}

std::string Player::serialize() const {
    std::ostringstream ss;
    ss << name << "|" << static_cast<int>(charClass) << "|"
       << health << "|" << maxHealth << "|" << attack << "|" << defense << "|"
       << gold << "|" << level << "|" << experience << "|" << expToNextLevel << "|"
       << karma << "|" << inventory.size();
    for (const auto& item : inventory) {
        ss << "|" << item.name << "|" << item.description << "|"
           << item.healAmount << "|" << item.attackBoost << "|" << item.defenseBoost << "|"
           << item.isConsumable << "|" << item.isKeyItem;
    }
    return ss.str();
}

void Player::deserialize(const std::string& data) {
    std::istringstream ss(data);
    std::string token;
    auto next = [&]() -> std::string {
        std::getline(ss, token, '|');
        return token;
    };

    name = next();
    charClass = static_cast<CharacterClass>(std::stoi(next()));
    health = std::stoi(next());
    maxHealth = std::stoi(next());
    attack = std::stoi(next());
    defense = std::stoi(next());
    gold = std::stoi(next());
    level = std::stoi(next());
    experience = std::stoi(next());
    expToNextLevel = std::stoi(next());
    karma = std::stoi(next());
    int itemCount = std::stoi(next());
    inventory.clear();
    for (int i = 0; i < itemCount; i++) {
        Item item;
        item.name = next();
        item.description = next();
        item.healAmount = std::stoi(next());
        item.attackBoost = std::stoi(next());
        item.defenseBoost = std::stoi(next());
        item.isConsumable = std::stoi(next()) != 0;
        item.isKeyItem = std::stoi(next()) != 0;
        inventory.push_back(item);
    }
}
