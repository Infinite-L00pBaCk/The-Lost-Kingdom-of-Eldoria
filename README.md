# The Lost Kingdom of Eldoria

### A Text-Based Adventure Game in C++

> **Pinnacle Labs Internship Task** — Create an interactive text-based game in C++, offering a captivating story, user choices, and variable outcomes.

---

## Overview

**The Lost Kingdom of Eldoria** is an immersive text-based adventure game where players take on the role of a wanderer who discovers a mysterious map leading to a lost kingdom. Navigate through enchanted forests, ancient ruins, and dark dungeons while making choices that shape your destiny.

## Features

| Feature | Description |
|---|---|
| **Branching Storyline** | 25+ story nodes with meaningful player choices |
| **Multiple Endings** | 5 distinct endings (Hero, Dark, Guardian, Ascended, Death) |
| **Character Classes** | Warrior, Mage, and Rogue — each with unique stats and abilities |
| **Turn-Based Combat** | Strategic combat with Attack, Defend, Use Item, and Flee options |
| **Inventory System** | Collect, manage, and use items throughout your journey |
| **Karma System** | Moral choices affect story outcomes and unlock secret endings |
| **Save/Load** | Persistent game saves with auto-save at checkpoints |
| **Visual Polish** | Typewriter text effects, colored console output, ASCII art, health bars |

## How to Compile & Run

### Prerequisites
- A C++ compiler supporting C++17 (g++, MSVC, or Clang)

### Compile
```bash
g++ -o eldoria main.cpp Game.cpp Player.cpp Story.cpp Combat.cpp Utils.cpp SaveSystem.cpp -std=c++17
```

### Run
```bash
# Windows
eldoria.exe

# Linux/Mac
./eldoria
```

## Game Architecture

```
main.cpp          → Entry point, launches Game engine
Game.h/.cpp       → Core state machine (menu, creation, story flow, combat routing)
Player.h/.cpp     → Player stats, inventory, leveling, karma, serialization
Story.h/.cpp      → Narrative graph — 25+ StoryNodes with choices and branches
Combat.h/.cpp     → Turn-based combat engine with 6 enemy types
Utils.h/.cpp      → Console colors, typewriter effect, input validation, menus
SaveSystem.h/.cpp → File-based save/load with auto-save at checkpoints
```

## Story Structure

```
Prologue: The Discovery
    ├── Act 1: The Enchanted Forest
    │   ├── Main Trail (combat encounters)
    │   ├── Hidden Path (hermit — moral choices)
    │   ├── Mushroom Grove (key item)
    │   └── Misty Ravine (equipment)
    ├── Act 2: The Ancient Ruins
    │   ├── Grand Hall (Crystal of Light — boss)
    │   ├── Ruined Library (lore & healing)
    │   └── Underground Passage (bandits — moral choices)
    └── Act 3: The Dark Dungeon
        ├── Dungeon Depths (combat)
        ├── Dungeon Cells (supplies & lore)
        └── Throne Room (Shadow Dragon — FINAL BOSS)
            ├── Ending 1: The Dark Sovereign (evil)
            ├── Ending 2: The Restorer (hero)
            ├── Ending 3: The Guardian (neutral)
            ├── Ending 4: The Ascended (secret — requires high karma + artifacts)
            └── Ending 5: Fallen Adventurer (death)
```

## Character Classes

| Class | HP | ATK | DEF | Special |
|---|---|---|---|---|
| **Warrior** | 150 | 12 | 8 | High survivability |
| **Mage** | 90 | 18 | 4 | 25% critical hit chance |
| **Rogue** | 110 | 14 | 6 | +50 starting gold, 75% flee chance |

## OOP Design Patterns Used

- **State Machine Pattern** — `GameState` enum drives the main game loop
- **Factory Pattern** — Enemy creation via factory functions (`createForestWolf()`, etc.)
- **Graph/Node Pattern** — Story nodes form a directed graph for branching narrative
- **Serialization Pattern** — Player state serialized to/from strings for file persistence
- **Singleton-like Pattern** — `Story` class initializes all nodes once in constructor

## Key Technical Concepts

- **Modular OOP Design** — Clean separation into header/implementation file pairs
- **STL Containers** — `std::vector` for inventory, `std::map` for story graph
- **File I/O** — Save/load system using `fstream`
- **Random Number Generation** — Mersenne Twister (`std::mt19937`) for combat randomness
- **Platform-Specific Code** — Windows API for console colors (`#ifdef _WIN32`)
- **Input Validation** — Robust handling of invalid user input throughout

---

*Developed for Pinnacle Labs Internship Task — Text-Based Adventure Game in C++*
