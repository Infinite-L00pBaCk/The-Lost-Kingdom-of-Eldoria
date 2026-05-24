#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

struct Item {
    std::string name;
    std::string description;
    int healAmount;
    int attackBoost;
    int defenseBoost;
    bool isConsumable;
    bool isKeyItem;

    Item(const std::string& n = "", const std::string& desc = "",
         int heal = 0, int atkBoost = 0, int defBoost = 0,
         bool consumable = true, bool key = false)
        : name(n), description(desc), healAmount(heal),
          attackBoost(atkBoost), defenseBoost(defBoost),
          isConsumable(consumable), isKeyItem(key) {}
};

enum class CharacterClass { WARRIOR, MAGE, ROGUE };

class Player {
private:
    std::string name;
    CharacterClass charClass;
    int health, maxHealth, attack, defense, gold;
    int level, experience, expToNextLevel;
    int karma;
    std::vector<Item> inventory;

public:
    Player();
    void setName(const std::string& playerName);
    void setClass(CharacterClass cls);

    std::string getName() const;
    CharacterClass getClass() const;
    std::string getClassName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttack() const;
    int getDefense() const;
    int getGold() const;
    int getLevel() const;
    int getExperience() const;
    int getExpToNextLevel() const;
    int getKarma() const;
    const std::vector<Item>& getInventory() const;

    void takeDamage(int amount);
    void heal(int amount);
    bool isAlive() const;
    void fullHeal();
    void addAttack(int amount);
    void addDefense(int amount);
    void addGold(int amount);
    bool spendGold(int amount);
    void addExperience(int amount);
    void addKarma(int amount);
    std::string getKarmaTitle() const;

    bool addItem(const Item& item);
    bool useItem(int index);
    bool removeItem(int index);
    bool hasItem(const std::string& itemName) const;

    void displayStats() const;
    void displayInventory() const;

    std::string serialize() const;
    void deserialize(const std::string& data);
};

#endif
