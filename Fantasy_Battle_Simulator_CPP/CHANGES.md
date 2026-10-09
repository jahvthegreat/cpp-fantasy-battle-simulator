# Changes made for portfolio preparation

The original class assignment files were **not overwritten**. This folder is an independently edited copy.

- `characterTpl.h`: Separates maximum health (`m_healthMax`) and current health (`m_health`); properly initializes the health policy type, applies damage to it, and maintains a valid maximum. Fixes the crash caused by maximum health becoming zero during a fight.
- `archer.h`, `barbarian.h`, `rogue.h`, `characterTpl.h`, `guild.h`, `team.h`, `guild.cpp`, `team.cpp`: Removed obsolete commented-out versions at file beginnings, without changing active combat and collection logic. Added explicit `<utility>` includes for move operations.
- `tests/health_smoke.cpp`: Added focused regression checks for ordinary health, `SuperHealth`, and `InfiniteHealth`.
- `README.md`: Added accurate build instructions and scope, plus academic-sharing and attribution notes.
- `.gitignore`: Prevents committing local binaries and debug artifacts.

## Verification

- GCC 14 with C++17 and AddressSanitizer/UndefinedBehaviorSanitizer: full `tester_1.cpp` run completed normally (T1 through T11).
- Clang with C++17: full test driver completed normally. Two warnings are intentional self-assignment checks in `tester_1.cpp`.
- Additional health regression test passed under sanitizers.
