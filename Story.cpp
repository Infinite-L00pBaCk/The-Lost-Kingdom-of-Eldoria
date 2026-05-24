#include "Story.h"

Story::Story() { buildStory(); }

const StoryNode& Story::getNode(int id) const {
    return nodes.at(id);
}

bool Story::hasNode(int id) const {
    return nodes.count(id) > 0;
}

void Story::buildStory() {
    StoryNode n;

    // ═══ NODE 1: PROLOGUE ═══
    n = StoryNode();
    n.id = 1;
    n.title = "The Discovery";
    n.narrative =
        "You are a wanderer, traveling through the outskirts of a forgotten village.\n"
        "Rain hammers against your cloak as lightning splits the sky.\n\n"
        "Seeking shelter, you stumble into an abandoned library. Dusty tomes line\n"
        "the walls, and cobwebs drape across ancient furniture.\n\n"
        "As you brush dust off a table, your hand catches on a loose stone.\n"
        "Beneath it lies a weathered scroll — a MAP, marked with a golden seal.\n\n"
        "The seal reads: 'The Lost Kingdom of Eldoria — Gateway to Eternal Power.'\n"
        "A path is traced through the Enchanted Forest, past Ancient Ruins,\n"
        "and into the heart of a mountain — the Dark Dungeon.\n\n"
        "Your heart races. This could be the adventure of a lifetime.";
    n.hasItemReward = true;
    n.itemReward = Item("Ancient Map", "A map to the Lost Kingdom of Eldoria", 0, 0, 0, false, true);
    n.choices.push_back(Choice("Study the map carefully and prepare to follow it", 2));
    n.choices.push_back(Choice("Take the map but rest for the night first", 3));
    nodes[1] = n;

    // ═══ NODE 2: IMMEDIATE DEPARTURE ═══
    n = StoryNode();
    n.id = 2;
    n.title = "Into the Storm";
    n.narrative =
        "Excitement overwhelms caution. You stuff the map into your pack and\n"
        "stride back into the storm. The wind howls, but the map's markings\n"
        "glow faintly with enchanted ink, guiding your way.\n\n"
        "After an hour of treacherous hiking, you reach the edge of the\n"
        "ENCHANTED FOREST. The trees tower impossibly high, their leaves\n"
        "shimmering with an ethereal silver light despite the storm.\n\n"
        "Two paths diverge before you:";
    n.choices.push_back(Choice("Take the main trail through the forest", 4));
    n.choices.push_back(Choice("Follow a faint, hidden path marked on the map", 5));
    nodes[2] = n;

    // ═══ NODE 3: REST FIRST ═══
    n = StoryNode();
    n.id = 3;
    n.title = "A Night's Rest";
    n.narrative =
        "Wisdom guides you to rest. You build a small fire from old books\n"
        "(only the ones already ruined by water, of course) and sleep\n"
        "through the storm.\n\n"
        "You awaken refreshed, the morning sun casting golden rays through\n"
        "the broken windows. You find a healing herb growing near the library.";
    n.healAmount = 30;
    n.hasItemReward = true;
    n.itemReward = Item("Healing Herb", "Restores 30 HP", 30);
    n.choices.push_back(Choice("Head to the Enchanted Forest", 4));
    n.choices.push_back(Choice("Search the library more before leaving", 6));
    nodes[3] = n;

    // ═══ NODE 4: MAIN FOREST TRAIL ═══
    n = StoryNode();
    n.id = 4;
    n.title = "The Enchanted Forest — Main Trail";
    n.narrative =
        "You walk the main trail. The forest is alive with strange sounds —\n"
        "whispers in languages you don't understand, glowing mushrooms that\n"
        "pulse like heartbeats, and vines that seem to part for your passage.\n\n"
        "Suddenly, a FOREST WOLF leaps from the underbrush, blocking your path!\n"
        "Its eyes glow an unnatural green.";
    n.hasCombat = true;
    n.enemyType = 1; // Forest Wolf
    n.choices.push_back(Choice("Continue deeper into the forest", 7));
    n.choices.push_back(Choice("Investigate the glowing mushrooms nearby", 8));
    nodes[4] = n;

    // ═══ NODE 5: HIDDEN PATH ═══
    n = StoryNode();
    n.id = 5;
    n.title = "The Hidden Path";
    n.narrative =
        "The hidden path winds through a dense thicket. Thorns scratch your\n"
        "arms, but the map's glow intensifies — you're on the right track.\n\n"
        "You emerge into a moonlit clearing where an OLD HERMIT sits by a fire.\n"
        "He looks up with milky white eyes.\n\n"
        "\"Ah, another seeker of Eldoria,\" he rasps. \"I can help you... for a price.\n"
        "Or you can take what I know by force. Your choice reveals your soul.\"";
    n.choices.push_back(Choice("Listen to the hermit and offer 20 gold for his wisdom", 9, 5));
    n.choices.push_back(Choice("Threaten the hermit for information", 10, -10));
    n.choices.push_back(Choice("Politely decline and continue on your own", 7, 2));
    nodes[5] = n;

    // ═══ NODE 6: SEARCH LIBRARY ═══
    n = StoryNode();
    n.id = 6;
    n.title = "Hidden Knowledge";
    n.narrative =
        "You search the library more thoroughly. Behind a false wall,\n"
        "you discover a small chest containing a shimmering blue potion\n"
        "and an old journal.\n\n"
        "The journal speaks of Eldoria's last king, who sealed the kingdom\n"
        "with a powerful spell. Three artifacts are needed to break the seal:\n"
        "the Crystal of Light, the Shadow Amulet, and the Dragon's Heart.\n\n"
        "This knowledge could prove invaluable.";
    n.hasItemReward = true;
    n.itemReward = Item("Mana Potion", "Restores 50 HP and boosts ATK +2", 50, 2);
    n.choices.push_back(Choice("Head to the Enchanted Forest", 4));
    nodes[6] = n;

    // ═══ NODE 7: DEEPER FOREST ═══
    n = StoryNode();
    n.id = 7;
    n.title = "Heart of the Forest";
    n.narrative =
        "You push deeper into the Enchanted Forest. The canopy grows so thick\n"
        "that the sky vanishes. Bioluminescent flowers light your way.\n\n"
        "You come upon a fork: one path leads to a BRIDGE over a roaring river;\n"
        "the other descends into a MISTY RAVINE.";
    n.choices.push_back(Choice("Cross the bridge", 11));
    n.choices.push_back(Choice("Descend into the misty ravine", 12));
    nodes[7] = n;

    // ═══ NODE 8: GLOWING MUSHROOMS ═══
    n = StoryNode();
    n.id = 8;
    n.title = "The Mushroom Grove";
    n.narrative =
        "You kneel beside the glowing mushrooms. They pulse with warmth.\n"
        "As you touch one, visions flash before your eyes — you see the\n"
        "ancient kingdom of Eldoria in its glory, with crystal spires\n"
        "reaching toward the heavens.\n\n"
        "The vision fades, leaving you with renewed vigor and a strange\n"
        "Crystal Shard that materialized in your hand.";
    n.healAmount = 20;
    n.hasItemReward = true;
    n.itemReward = Item("Crystal Shard", "A fragment of Eldorian crystal — key item", 0, 0, 0, false, true);
    n.choices.push_back(Choice("Continue deeper into the forest", 7));
    nodes[8] = n;

    // ═══ NODE 9: HERMIT HELPS (GOOD) ═══
    n = StoryNode();
    n.id = 9;
    n.title = "The Hermit's Wisdom";
    n.narrative =
        "You offer the hermit gold. He smiles warmly.\n\n"
        "\"Kindness is rare these days. Listen well: the Shadow Dragon guards\n"
        "Eldoria's throne room. It feeds on darkness — anger, greed, cruelty.\n"
        "But it is weakened by light and virtue.\n\n"
        "Take this amulet. It was forged in Eldoria's last days.\"\n\n"
        "He presses a glowing amulet into your hands.";
    n.hasItemReward = true;
    n.itemReward = Item("Light Amulet", "Weakens creatures of shadow — key item", 0, 0, 3, false, true);
    n.choices.push_back(Choice("Thank him and continue into the forest", 7));
    nodes[9] = n;

    // ═══ NODE 10: THREATEN HERMIT (EVIL) ═══
    n = StoryNode();
    n.id = 10;
    n.title = "The Hermit's Curse";
    n.narrative =
        "You draw your weapon and threaten the old man. He doesn't flinch.\n\n"
        "\"Fool. You choose the path of shadows.\"\n\n"
        "He throws a pouch of gold at your feet and vanishes in a swirl\n"
        "of smoke, but not before whispering a curse that chills your blood.\n\n"
        "You feel slightly weaker, but richer.";
    n.choices.push_back(Choice("Shrug it off and continue into the forest", 7));
    nodes[10] = n;

    // ═══ NODE 11: THE BRIDGE ═══
    n = StoryNode();
    n.id = 11;
    n.title = "The Bridge Crossing";
    n.narrative =
        "The old wooden bridge sways dangerously over the churning river.\n"
        "Halfway across, a GOBLIN SCOUT jumps up from beneath the planks!\n\n"
        "\"Toll! Toll for the bridge!\" it shrieks, waving a rusty blade.";
    n.hasCombat = true;
    n.enemyType = 2; // Goblin Scout
    n.choices.push_back(Choice("Cross to the Ancient Ruins beyond", 13));
    nodes[11] = n;

    // ═══ NODE 12: MISTY RAVINE ═══
    n = StoryNode();
    n.id = 12;
    n.title = "The Misty Ravine";
    n.narrative =
        "You descend into the mist-filled ravine. Visibility drops to\n"
        "almost nothing. Strange echoes bounce off the walls.\n\n"
        "You stumble upon a hidden cave. Inside, you find an abandoned\n"
        "campsite with supplies and a shimmering sword embedded in stone.";
    n.hasItemReward = true;
    n.itemReward = Item("Enchanted Blade", "A magical sword — ATK +5", 0, 5, 0, false, false);
    n.choices.push_back(Choice("Climb out and head to the Ancient Ruins", 13));
    n.choices.push_back(Choice("Explore the cave further", 14));
    nodes[12] = n;

    // ═══ NODE 13: ANCIENT RUINS ENTRANCE ═══
    n = StoryNode();
    n.id = 13;
    n.title = "The Ancient Ruins";
    n.narrative =
        "You emerge from the forest into a vast clearing. Before you stand\n"
        "the ANCIENT RUINS of what was once a magnificent city. Crumbling\n"
        "pillars reach toward the sky, covered in moss and ivy.\n\n"
        "Faded inscriptions on the walls tell of Eldoria's golden age.\n"
        "Three paths lead deeper into the ruins:";
    n.choices.push_back(Choice("Enter the Grand Hall", 15));
    n.choices.push_back(Choice("Explore the Ruined Library", 16));
    n.choices.push_back(Choice("Investigate the Underground Passage", 17));
    nodes[13] = n;

    // ═══ NODE 14: DEEP CAVE ═══
    n = StoryNode();
    n.id = 14;
    n.title = "The Deep Cave";
    n.narrative =
        "Deeper in the cave, you find ancient Eldorian carvings. They depict\n"
        "a great battle between the kingdom and a shadow dragon.\n\n"
        "Suddenly, a SKELETON WARRIOR animates from a pile of bones,\n"
        "the ancient guardian of this sacred place!";
    n.hasCombat = true;
    n.enemyType = 3; // Skeleton Warrior
    n.hasItemReward = true;
    n.itemReward = Item("Guardian's Shield", "An ancient shield — DEF +4", 0, 0, 4, false, false);
    n.choices.push_back(Choice("Take the shield and head to the Ancient Ruins", 13));
    nodes[14] = n;

    // ═══ NODE 15: GRAND HALL ═══
    n = StoryNode();
    n.id = 15;
    n.title = "The Grand Hall";
    n.narrative =
        "The Grand Hall is enormous. Shattered chandeliers hang from the ceiling.\n"
        "A faded red carpet leads to a raised platform where a throne once stood.\n\n"
        "On the platform, you find a PEDESTAL with a glowing crystal floating above it.\n"
        "This must be the Crystal of Light!\n\n"
        "But a DARK MAGE stands guard, dark energy swirling around them.\n"
        "\"The crystal stays with me, adventurer!\"";
    n.hasCombat = true;
    n.enemyType = 4; // Dark Mage
    n.hasItemReward = true;
    n.itemReward = Item("Crystal of Light", "One of three artifacts of Eldoria — key item", 0, 0, 0, false, true);
    n.choices.push_back(Choice("Take the crystal and explore more of the ruins", 18));
    n.choices.push_back(Choice("Head directly to the dungeon entrance", 20));
    nodes[15] = n;

    // ═══ NODE 16: RUINED LIBRARY ═══
    n = StoryNode();
    n.id = 16;
    n.title = "The Ruined Library";
    n.narrative =
        "Thousands of books lie scattered among fallen shelves. You search\n"
        "through the debris and find a tome titled 'The Dragon's Weakness.'\n\n"
        "It reads: 'The Shadow Dragon draws power from the darkness within\n"
        "those who challenge it. A pure heart weakens it. The Light Amulet\n"
        "and Crystal of Light together can banish its shadow armor.'\n\n"
        "You also find healing supplies hidden in a desk.";
    n.hasItemReward = true;
    n.itemReward = Item("Greater Healing Potion", "Restores 80 HP", 80);
    n.healAmount = 40;
    n.choices.push_back(Choice("Go to the Grand Hall", 15));
    n.choices.push_back(Choice("Check the Underground Passage", 17));
    nodes[16] = n;

    // ═══ NODE 17: UNDERGROUND PASSAGE ═══
    n = StoryNode();
    n.id = 17;
    n.title = "The Underground Passage";
    n.narrative =
        "The passage descends into darkness. Your torch flickers as cold\n"
        "air rushes up from below.\n\n"
        "You encounter a BANDIT LEADER and their gang using the ruins as\n"
        "a hideout. They've been robbing travelers.\n\n"
        "\"Well, well... another lamb to the slaughter,\" the leader grins.";
    n.choices.push_back(Choice("Fight the Bandit Leader", 19));
    n.choices.push_back(Choice("Try to negotiate — offer 30 gold for safe passage", 21, 0));
    n.choices.push_back(Choice("Convince them to join your cause against the dragon", 22, 5));
    nodes[17] = n;

    // ═══ NODE 18: RUINS EXPLORATION ═══
    n = StoryNode();
    n.id = 18;
    n.title = "Deeper in the Ruins";
    n.narrative =
        "With the Crystal of Light in hand, you explore further.\n"
        "You discover a hidden shrine with a healing fountain.\n"
        "The crystal glows brighter as you approach, and the fountain\n"
        "springs to life, its waters shimmering with golden light.\n\n"
        "You drink deeply and feel your wounds mending.";
    n.healAmount = 999; // Full heal
    n.choices.push_back(Choice("Proceed to the Dark Dungeon", 20));
    nodes[18] = n;

    // ═══ NODE 19: FIGHT BANDITS ═══
    n = StoryNode();
    n.id = 19;
    n.title = "Bandit Showdown";
    n.narrative =
        "You draw your weapon. The other bandits scatter, leaving their\n"
        "cowardly leader alone.";
    n.hasCombat = true;
    n.enemyType = 5; // Bandit Leader
    n.hasItemReward = true;
    n.itemReward = Item("Shadow Amulet", "Dark artifact — one of three keys — key item", 0, 3, 0, false, true);
    n.choices.push_back(Choice("Take the Shadow Amulet and head to the dungeon", 20));
    nodes[19] = n;

    // ═══ NODE 20: DUNGEON ENTRANCE ═══
    n = StoryNode();
    n.id = 20;
    n.title = "The Dark Dungeon — Entrance";
    n.narrative =
        "The entrance to the Dark Dungeon looms before you — a massive stone\n"
        "doorway carved with dragons and runic symbols. The air is frigid.\n\n"
        "Beyond this door lies the heart of Eldoria, and the Shadow Dragon\n"
        "that guards its secrets. There is no turning back.\n\n"
        "You notice an inscription: 'Only those who carry the light may\n"
        "hope to survive the darkness within.'";
    n.choices.push_back(Choice("Enter the dungeon with courage", 23));
    n.choices.push_back(Choice("Rest and prepare before entering", 24));
    nodes[20] = n;

    // ═══ NODE 21: NEGOTIATE WITH BANDITS ═══
    n = StoryNode();
    n.id = 21;
    n.title = "A Deal with Thieves";
    n.narrative =
        "You toss a pouch of gold to the bandit leader. He catches it\n"
        "and bites a coin, grinning.\n\n"
        "\"Smart one. Pass through, but know this — we found a dark amulet\n"
        "deeper in. Take it if you want, it gave us nightmares.\"\n\n"
        "He steps aside and points to a chest in the corner.";
    n.hasItemReward = true;
    n.itemReward = Item("Shadow Amulet", "Dark artifact — one of three keys — key item", 0, 3, 0, false, true);
    n.choices.push_back(Choice("Take the amulet and head to the dungeon", 20));
    nodes[21] = n;

    // ═══ NODE 22: CONVINCE BANDITS ═══
    n = StoryNode();
    n.id = 22;
    n.title = "Unlikely Allies";
    n.narrative =
        "You speak passionately about the dragon and the lost kingdom.\n"
        "The bandit leader's eyes widen.\n\n"
        "\"My grandmother told stories of Eldoria... Fine. We won't fight\n"
        "alongside you, but take this — and our blessing.\"\n\n"
        "They give you supplies and the dark amulet they found.";
    n.hasItemReward = true;
    n.itemReward = Item("Shadow Amulet", "Dark artifact — one of three keys — key item", 0, 3, 0, false, true);
    n.healAmount = 50;
    n.choices.push_back(Choice("Thank them and head to the dungeon", 20));
    nodes[22] = n;

    // ═══ NODE 23: DUNGEON INTERIOR ═══
    n = StoryNode();
    n.id = 23;
    n.title = "The Dark Dungeon — Depths";
    n.narrative =
        "The dungeon is a labyrinth of shadow and stone. Torches flicker\n"
        "with blue flame that provides no warmth. The walls seem to breathe.\n\n"
        "A SKELETON WARRIOR blocks a narrow corridor, ancient duty still\n"
        "burning in its hollow eyes.";
    n.hasCombat = true;
    n.enemyType = 3; // Skeleton
    n.choices.push_back(Choice("Press onward to the throne room", 25));
    n.choices.push_back(Choice("Search the dungeon cells for supplies", 26));
    nodes[23] = n;

    // ═══ NODE 24: REST BEFORE DUNGEON ═══
    n = StoryNode();
    n.id = 24;
    n.title = "Final Preparations";
    n.narrative =
        "You make camp near the dungeon entrance. The stars are\n"
        "extraordinarily bright, as if watching your journey.\n\n"
        "You sharpen your weapons, tend your wounds, and mentally\n"
        "prepare for what lies ahead. You feel ready.";
    n.healAmount = 999;
    n.hasItemReward = true;
    n.itemReward = Item("Elixir of Courage", "Fully restores HP and boosts ATK +3", 999, 3);
    n.choices.push_back(Choice("Enter the dungeon at dawn", 23));
    nodes[24] = n;

    // ═══ NODE 25: THRONE ROOM ═══
    n = StoryNode();
    n.id = 25;
    n.title = "The Throne Room";
    n.narrative =
        "You enter a cavernous chamber. On a throne of black obsidian sits\n"
        "a colossal SHADOW DRAGON. Its scales shimmer like liquid darkness,\n"
        "and its crimson eyes lock onto you.\n\n"
        "\"MORTAL,\" it thunders. \"You dare enter MY domain?\n"
        "Countless have tried. All have fallen. You will be no different.\"\n\n"
        "The dragon rises, spreading wings that blot out the ceiling.\n"
        "This is it — the final battle.";
    n.hasCombat = true;
    n.enemyType = 6; // Shadow Dragon (BOSS)
    // After combat, routing depends on karma and items — handled in Game.cpp
    n.choices.push_back(Choice("Claim the throne of Eldoria for yourself", 30, -10));
    n.choices.push_back(Choice("Restore the kingdom to its former glory", 31, 10));
    n.choices.push_back(Choice("Seal the kingdom away forever to protect the world", 32, 5));
    nodes[25] = n;

    // ═══ NODE 26: DUNGEON CELLS ═══
    n = StoryNode();
    n.id = 26;
    n.title = "The Dungeon Cells";
    n.narrative =
        "The cells hold the remains of past adventurers. Among them,\n"
        "you find a powerful healing potion and a journal.\n\n"
        "The journal's last entry reads: 'If you have the Crystal, the\n"
        "Amulet, and a pure heart, the dragon CAN be defeated. It fears\n"
        "those who resist its temptation of power.'";
    n.hasItemReward = true;
    n.itemReward = Item("Supreme Healing Potion", "Restores 150 HP", 150);
    n.choices.push_back(Choice("Head to the throne room", 25));
    nodes[26] = n;

    // ═══ ENDINGS ═══

    // NODE 30: DARK ENDING — Claim Throne
    n = StoryNode();
    n.id = 30;
    n.title = "Ending: The Dark Sovereign";
    n.narrative =
        "You ascend the obsidian throne. Shadow energy courses through you,\n"
        "transforming your very being. Power beyond imagination fills your veins.\n\n"
        "But with it comes a terrible hunger — for conquest, for domination.\n"
        "The shadows whisper promises of glory, and you listen.\n\n"
        "You become the new ruler of the darkness, feared by all.\n"
        "The Lost Kingdom of Eldoria remains lost, now YOUR fortress of shadow.\n\n"
        "The world trembles at the rise of a new Dark Sovereign.";
    n.isEnding = true;
    n.endingTitle = "THE DARK SOVEREIGN — Evil Ending";
    nodes[30] = n;

    // NODE 31: GOOD ENDING — Restore Kingdom
    n = StoryNode();
    n.id = 31;
    n.title = "Ending: The Restorer";
    n.narrative =
        "You raise the Crystal of Light high. Golden energy floods the throne\n"
        "room, banishing the shadows. The ruins begin to TRANSFORM.\n\n"
        "Walls rebuild themselves. Gardens bloom from barren stone.\n"
        "Crystal spires rise toward the heavens, just as in the ancient visions.\n\n"
        "The people of nearby villages, drawn by the light, come to witness\n"
        "the miracle. They hail you as the Restorer of Eldoria.\n\n"
        "Under your guidance, the kingdom flourishes once more — a beacon\n"
        "of hope and prosperity for all the land.";
    n.isEnding = true;
    n.endingTitle = "THE RESTORER — Hero Ending";
    nodes[31] = n;

    // NODE 32: NEUTRAL ENDING — Seal Kingdom
    n = StoryNode();
    n.id = 32;
    n.title = "Ending: The Guardian";
    n.narrative =
        "You use the artifacts to reinforce the ancient seals. The kingdom\n"
        "shimmers and fades, becoming invisible to the mortal world.\n\n"
        "The power within is too dangerous for anyone — including you.\n"
        "You walk away, knowing you've protected the world from a force\n"
        "that could corrupt even the purest of hearts.\n\n"
        "You become a wandering guardian, forever watching over the sealed\n"
        "kingdom, ensuring no one disturbs its slumber.\n\n"
        "History forgets Eldoria, but you remember. And you keep watch.";
    n.isEnding = true;
    n.endingTitle = "THE GUARDIAN — Neutral Ending";
    nodes[32] = n;

    // NODE 33: SECRET ENDING — Pure Heart + All Artifacts
    n = StoryNode();
    n.id = 33;
    n.title = "Ending: The Ascended";
    n.narrative =
        "The Crystal of Light, Shadow Amulet, and your pure heart resonate\n"
        "together, creating a harmonic frequency that transcends mortal magic.\n\n"
        "The entire dungeon dissolves into pure white light. You float upward,\n"
        "your body transforming into something beyond human.\n\n"
        "You become the IMMORTAL GUARDIAN of Eldoria — neither king nor servant,\n"
        "but a being of pure light who protects the kingdom across all dimensions.\n\n"
        "The kingdom exists in eternal peace, guided by your infinite wisdom.\n"
        "Legends speak of a wanderer who became a god.";
    n.isEnding = true;
    n.endingTitle = "THE ASCENDED — Secret True Ending";
    nodes[33] = n;

    // NODE 34: DEATH ENDING
    n = StoryNode();
    n.id = 34;
    n.title = "Ending: Fallen Adventurer";
    n.narrative =
        "Your journey ends here, in the depths of the dark dungeon.\n"
        "The shadows consume your fallen form, adding you to the\n"
        "countless adventurers who sought Eldoria and failed.\n\n"
        "Perhaps one day, another brave soul will find your journal\n"
        "and learn from your mistakes. The kingdom waits, patient\n"
        "and eternal, for a worthier challenger.\n\n"
        "Your story becomes a cautionary tale whispered in taverns\n"
        "across the land.";
    n.isEnding = true;
    n.endingTitle = "FALLEN ADVENTURER — Death Ending";
    nodes[34] = n;
}
