<div align="center">

```
  _____ _            _              _   
 |_   _| |__   ___  | |    ___  ___| |_      
   | | | '_ \ / _ \ | |   / _ \/ __| __|
   | | | | | |  __/ | |__| (_) \__ \ |_ 
   |_| |_| |_|\___| |_____\___/|___/\__|

  _  ___                 _                
 | |/ (_)_ __   __ _  __| | ___  _ __ ___
 | ' /| | '_ \ / _` |/ _` |/ _ \| '_ ` _ \
 | . \| | | | | (_| | (_| | (_) | | | | | |
 |_|\_\_|_| |_|\__, |\__,_|\___/|_| |_| |_|
               |___/                      

  ___   __   _____ _     _            _       
 / _ \ / _| | ____| | __| | ___  _ __(_) __ _ 
| | | | |_  |  _| | |/ _` |/ _ \| '__| |/ _` |
| |_| |  _| | |___| | (_| | (_) | |  | | (_| |
 \___/|_|   |_____|_|\__,_|\___/|_|  |_|\__,_|
```

**A Text-Based Adventure Game in C++**

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)
![Internship](https://img.shields.io/badge/Pinnacle%20Labs-Internship%20Task-orange?style=for-the-badge)

*Navigate treacherous forests, ancient ruins, and dark dungeons. Every choice shapes your fate.*

</div>

---

## ⚔️ Overview 

**The Lost Kingdom of Eldoria** is an immersive, story-driven text-based adventure game built entirely in C++. You play as a wanderer who stumbles upon an ancient map leading to a kingdom lost to time — sealed away by dark magic, forgotten by the world. What you find there, and how you leave, depends entirely on the choices you make.

With **25+ story nodes**, **5 distinct endings**, **turn-based combat**, and a **karma system** that tracks your moral compass, every playthrough can tell a different story.

---

## ✨ Features

### 🗺️ Gameplay
| Feature | Details |
|---|---|
| **Branching Storyline** | 25+ interconnected story nodes with meaningful choices |
| **5 Unique Endings** | Hero, Dark Sovereign, Guardian, Ascended (secret), Fallen Adventurer |
| **Karma System** | Your moral choices accumulate and unlock different story paths |
| **Character Classes** | Warrior, Mage, and Rogue — each with unique stats and abilities |
| **Turn-Based Combat** | Strategic battles: Attack, Defend, Use Item, or Flee |
| **Inventory System** | 15-slot inventory with consumables, equipment, and key items |
| **Leveling System** | Gain XP, level up, and grow stronger throughout your journey |
| **Save / Load** | Persistent saves with auto-save at key story checkpoints |

### 🎨 Presentation
| Feature | Details |
|---|---|
| **Colored Console Text** | Windows Console API color-coding for immersive display |
| **Typewriter Effect** | Narrative text animates character-by-character |
| **Visual Health Bars** | Live HP bars for player and enemies during combat |
| **ASCII Art** | Styled title banner, victory screens, and Game Over display |
| **Input Validation** | Robust handling — no crashes from bad input |

---

## 🧙 Character Classes

| Class | HP | ATK | DEF | Special Ability |
|:---:|:---:|:---:|:---:|:---|
| ⚔️ **Warrior** | 150 | 12 | 8 | High survivability — built to endure |
| 🔮 **Mage** | 90 | 18 | 4 | 25% critical hit chance on every attack |
| 🗡️ **Rogue** | 110 | 14 | 6 | +50 starting gold · 75% flee success rate |

---

## 👾 Enemies

| Enemy | HP | ATK | DEF | Reward |
|:---|:---:|:---:|:---:|:---:|
| 🐺 Forest Wolf | 45 | 9 | 2 | 25 XP / 10 Gold |
| 👺 Goblin Scout | 55 | 11 | 3 | 35 XP / 20 Gold |
| 💀 Skeleton Warrior | 80 | 14 | 6 | 55 XP / 30 Gold |
| 🧙 Dark Mage | 65 | 20 | 4 | 70 XP / 45 Gold |
| 🔪 Bandit Leader | 90 | 16 | 7 | 60 XP / 50 Gold |
| 🐉 **Shadow Dragon** *(Boss)* | 200 | 25 | 12 | 200 XP / 100 Gold |

> 💡 **Tip:** Having the **Light Amulet** or **Crystal of Light** weakens the Shadow Dragon before the fight begins!

---

## 🗺️ Story Structure

```
📜 Prologue: The Discovery
│
├── 🌲 Act 1: The Enchanted Forest
│   ├── Main Trail        → Combat encounters, wolf attack
│   ├── Hidden Path       → The Hermit (moral choices, karma)
│   ├── Mushroom Grove    → Secret key item location
│   └── Misty Ravine      → Equipment and gear
│
├── 🏛️ Act 2: The Ancient Ruins
│   ├── Grand Hall        → Crystal of Light (boss fight)
│   ├── Ruined Library    → Lore, healing, knowledge
│   └── Underground Passage → Bandits (moral choices)
│
└── 🏰 Act 3: The Dark Dungeon
    ├── Dungeon Depths    → Combat gauntlet
    ├── Dungeon Cells     → Supplies and lore
    └── Throne Room       → ⚔️ FINAL BOSS: Shadow Dragon
        │
        ├── 👑 Ending 1: The Dark Sovereign  (claim the throne)
        ├── 🌟 Ending 2: The Restorer        (rebuild the kingdom)
        ├── 🛡️ Ending 3: The Guardian        (seal it forever)
        ├── ✨ Ending 4: The Ascended        (SECRET — karma ≥ 10 + both artifacts)
        └── 💀 Ending 5: Fallen Adventurer   (die in combat)
```

---

## 🏗️ Project Architecture

```
eldoria/
│
├── main.cpp            →  Entry point, console UTF-8 setup
├── Game.h / .cpp       →  State machine & core game loop
├── Player.h / .cpp     →  Stats, inventory, leveling, karma, serialization
├── Story.h / .cpp      →  Narrative graph — 25+ nodes with choices & branches
├── Combat.h / .cpp     →  Turn-based combat engine, 6 enemy types
├── Utils.h / .cpp      →  Console colors, typewriter, input validation, menus
├── SaveSystem.h / .cpp →  File-based save/load, auto-save at checkpoints
└── README.md           →  You are here
```

### Design Patterns Used
- **State Machine** — `GameState` enum drives the entire game loop
- **Factory Pattern** — Enemy creation via `createForestWolf()`, `createShadowDragon()`, etc.
- **Graph / Node Pattern** — Story nodes form a directed graph (`std::map<int, StoryNode>`)
- **Serialization Pattern** — Player state serialized to pipe-delimited strings for file save/load
- **Single Responsibility** — Each module has one clear job, cleanly separated into `.h` / `.cpp` pairs

---

## ⚙️ How to Compile & Run

### Prerequisites
- **Compiler:** g++ with C++17 support (MinGW recommended for Windows)
- **OS:** Windows 10 / 11
- Download MinGW from: https://www.mingw-w64.org/

### Compile
```bash
g++ -o eldoria.exe main.cpp Game.cpp Player.cpp Story.cpp Combat.cpp Utils.cpp SaveSystem.cpp -std=c++17
```

### Run
```bash
eldoria.exe
```

---

## 🎮 Sample Gameplay

```
+================================================+
|        THE LOST KINGDOM OF ELDORIA             |
+================================================+
     A Text-Based Adventure Game in C++

+-------------+
| MAIN MENU   |
+-------------+
  [1] New Game
  [2] About
  [3] Quit

>> 1

+---------------------+
| CHARACTER CREATION  |
+---------------------+

  Enter your name, adventurer: Priyam

  [1] WARRIOR   HP: 150 | ATK: 12 | DEF: 8
  [2] MAGE      HP: 90  | ATK: 18 | DEF: 4
  [3] ROGUE     HP: 110 | ATK: 14 | DEF: 6 | +50 Gold

>> 2

============================================================
                   ⚔  COMBAT ENCOUNTER  ⚔
============================================================

  A Forest Wolf appears!
  The wolf snarls, baring its fangs!

  Forest Wolf HP: [████████████████████] 45/45
  Your HP:     [████████████████████] 90/90

  What will you do?
    [1] Attack
    [2] Defend
    [3] Use Item
    [4] Flee
```

---

## 📊 Technical Highlights

| Concept | Implementation |
|:---|:---|
| OOP Encapsulation | All `Player` fields private, accessed via getters/setters |
| STL Containers | `std::vector` for inventory, `std::map` for story graph |
| File I/O | `fstream` for save/load with auto-save at nodes 13, 20, 25 |
| Randomness | Mersenne Twister (`std::mt19937`) for combat variance |
| Serialization | Pipe-delimited string format: `name\|class\|hp\|atk\|...` |
| Platform Code | `#ifdef _WIN32` for Windows-specific console color API |
| Input Safety | `cin.clear()` + `cin.ignore()` prevents input-related crashes |

---

## 🔮 Ending Guide (Spoilers!)

| Ending | How to Reach |
|:---|:---|
| 👑 **The Dark Sovereign** | Choose to claim the throne for yourself |
| 🌟 **The Restorer** | Choose to restore the kingdom to its people |
| 🛡️ **The Guardian** | Choose to seal the kingdom and walk away |
| ✨ **The Ascended** *(Secret)* | Karma ≥ 10 **+** own the Crystal of Light **+** own the Light Amulet |
| 💀 **Fallen Adventurer** | Die in any combat encounter |

---

## 🚀 Future Enhancements

- [ ] Multiple save slots
- [ ] Merchant / shop system using earned gold
- [ ] Difficulty levels (Easy / Normal / Hard)
- [ ] Procedurally generated side dungeons
- [ ] Achievement system
- [ ] Extended story with new chapters
- [ ] Linux/macOS color support via ANSI escape codes

---

## 👨‍💻 Developer

**Priyam Prakash**  
Internship Task Submission — Pinnacle Labs  
*May 2026*

---

<div align="center">

*"Every choice echoes through eternity. Choose wisely, adventurer."*

⭐ If you enjoyed this project, consider giving it a star!

</div>
