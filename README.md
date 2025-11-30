# Moonlight

> A Gothic 2D Platformer developed in C++ with SFML.

![Badge C++](https://img.shields.io/badge/C++-17-blue.svg?style=flat&logo=c%2B%2B)
![Badge SFML](https://img.shields.io/badge/SFML-2.6.2-green.svg?style=flat&logo=sfml)

![Graveyard](assets/stages/Graveyard.png)

## About

**Moonlight** is a project for the Programming Techniques course for the purpose of learning software engineering techniques, particularly object-oriented programming in C++. It features a 2D platformer adventure where can be played in multiplayer, explore two stages (Graveyard and Castle), battle enemies, and overcome deadly obstacles.

The project demonstrates advanced Object-Oriented Programming concepts, including:
- **Design Patterns:** Singleton, State and Template Method.
- **Data Structures:** Custom Template Linked List implementation.
- **Persistence:** Save/Load system and Leaderboard using JSON.

---

## Features

- **Two Game Modes:** Single-player or Local Co-op Multiplayer.
- **Two Distinct Stages:**
  - **Graveyard:** Haunted by skeletons and floating bats.
  - **Castle:** Guarded by the boss "Death", deadly spikes and skeletons.
- **Persistence System:**
  - Save and Load your progress (Level, Health, Position, Score).
  - Top 5 High Score Leaderboard.
- **Physics Engine:** Custom collision detection (AABB - Axis Aligned Bounding Box) and gravity simulation.
- **Entities:**
  - **Enemies:** Skeletons (Patrol), Bats (Flying/Tracking), Death (Boss/Shooter).
  - **Obstacles:** Mud Hands (Slow), Spikes (Damage), Platforms (increase bow damage).

---

## Controls

| Action | Player 1 | Player 2 | General |
| :--- | :---: | :---: | :---: |
| **Move Left** | `A` | `Left Arrow` | - |
| **Move Right** | `D` | `Right Arrow` | - |
| **Jump** | `W` | `Up Arrow` | - |
| **Attack** | `Space` | `L` | - |
| **Shoot Projectile**| `F` | - | - |
| **Pause Game** | - | - | `P` or `ESC` |
| **Menu Select** | `W` / `S` | - | `Enter` |

---

## Installation & Build

### Prerequisites

Ensure you have the following installed:
- [CMake](https://cmake.org/download/) (3.20+)
- [MinGW-w64](https://www.mingw-w64.org/) (or another C++ compiler)
- [SFML 2.6.2](https://www.sfml-dev.org/download.php)

### Dependencies
The project uses [nlohmann/json](https://github.com/nlohmann/json) for serialization (included in `include/utils`).

---

### Compiling on Linux

1. Clone the repository:
   ```bash
   git clone [https://github.com/LeoShibata/Projeto_Tec_Prog.git](https://github.com/LeoShibata/Projeto_Tec_Prog.git)
   cd build
   make
   ./SFMLgame


### Compiling on Windows

1. Clone the repository:
   ```bash
   git clone [https://github.com/LeoShibata/Projeto_Tec_Prog.git](https://github.com/LeoShibata/Projeto_Tec_Prog.git)
   cmake -G "MinGW Makefiles" -S . -B build -DSFML_DIR="C:/SFML-2.6.2/lib/cmake/SFML"
   cd build
   mingw32-make
   ./SFMLgame