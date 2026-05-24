#ifndef STORY_H
#define STORY_H

#include "Player.h"
#include <string>
#include <vector>
#include <map>
#include <functional>

struct Choice {
    std::string text;
    int nextNode;
    int karmaChange;       // 0 if no karma effect
    std::string requiredItem; // empty if no requirement

    Choice(const std::string& t, int next, int karma = 0, const std::string& req = "")
        : text(t), nextNode(next), karmaChange(karma), requiredItem(req) {}
};

struct StoryNode {
    int id;
    std::string title;
    std::string narrative;
    std::vector<Choice> choices;
    bool hasCombat;
    int enemyType;       // 0=none, 1=wolf, 2=goblin, 3=skeleton, 4=mage, 5=bandit, 6=dragon
    Item itemReward;
    bool hasItemReward;
    int healAmount;      // 0 = no heal
    bool isEnding;
    std::string endingTitle;

    StoryNode() : id(0), hasCombat(false), enemyType(0),
                  hasItemReward(false), healAmount(0), isEnding(false) {}
};

class Story {
private:
    std::map<int, StoryNode> nodes;
    void buildStory();

public:
    Story();
    const StoryNode& getNode(int id) const;
    bool hasNode(int id) const;
};

#endif
