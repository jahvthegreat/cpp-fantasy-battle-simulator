# Fantasy Character Combat Simulator (C++)

An **academic C++ project** that models fantasy characters, their weapons and abilities, and interactions between teams and guilds. The included test driver demonstrates character creation, copying/moving character collections, guild membership, and simulated battles.

> **Portfolio status:** This repository is prepared for **private** GitHub storage. Verify your course's academic-integrity and code-sharing rules before making any assignment or instructor-provided files public.

## Features

- **Character classes:** Archer, Barbarian, and Rogue, with different attack and defense behavior.
- **Generic programming:** class templates for health, abilities, and weapon types.
- **Runtime polymorphism:** a common abstract `Character` interface for different character subclasses.
- **Combat mechanics:** melee/ranged attacks, defenses, special abilities and cooldowns, and multiple health types.
- **Teams and guilds:** adding and removing characters, avoiding duplicates, and adjusting health on guild membership.
- **Resource management:** deep-copying character instances for teams, non-owning guild references, copy/move operations, and cleanup.
- **Demonstration scenarios:** tests for team and guild operations followed by turn-based simulated battles.

This is a **console-based simulation/test driver**, not a graphical or player-controlled game.

## Build and run

Requires a C++17-capable compiler (for example, Clang on macOS or GCC).

From the directory containing `tester_1.cpp`:

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic tester_1.cpp team.cpp guild.cpp -o fantasy-battle
./fantasy-battle
```

Or with GCC:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tester_1.cpp team.cpp guild.cpp -o fantasy-battle
./fantasy-battle
```

The test driver intentionally performs self-assignment checks (`copy = copy`); some compilers warn about those test lines.

### Optional health smoke test

```bash
clang++ -std=c++17 -I. tests/health_smoke.cpp -o health-smoke
./health-smoke
```

## Source layout

| File | Purpose |
| --- | --- |
| `character.h`, `characterTpl.h` | Abstract character interface and templated health implementation |
| `archer.h`, `barbarian.h`, `rogue.h` | Character specializations |
| `health.h`, `weapons.h`, `abilities.h` | Character health, weapons, and skills |
| `team.h`, `team.cpp` | Owns copies of members; implements copy/move operations |
| `guild.h`, `guild.cpp` | Groups non-owned character references |
| `tester_1.cpp` | Provided assignment-style integration/test driver |
| `tests/health_smoke.cpp` | Additional health regression checks for the portfolio copy |

## Portfolio cleanup and fixes

The portfolio copy is based on the submitted coursework, with the following changes:

1. Corrected `CharacterTpl` to store **maximum health separately from current health** and apply damage via the selected health type. This avoids the original division-by-zero crash during battle output.
2. Removed large obsolete **commented-out duplicate implementations** while retaining the active class designs.
3. Included an additional regression test for normal, reduced-damage, and infinite health.
4. Excluded compiled binaries and platform-specific debugging archives.

The original assignment upload is kept separate from this edited copy. All original test scenarios now complete in the corrected copy under GCC with address/undefined-behavior sanitizers. These checks don't guarantee the software is free of all defects.

## Coursework and attribution

Created as Seneca Polytechnic coursework and subsequently organized and debugged for a personal portfolio. The provided files may contain assignment scaffolding, starter definitions, or test code supplied by the course. Review your instructor's permissions and clearly credit any provided material before publishing. This repository makes no claim that every line was written independently.
