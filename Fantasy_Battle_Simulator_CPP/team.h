#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>

namespace seneca
{
    class Team
    {
        std::string label;
        Character** roster;
        size_t count;

        void cleanupRoster();

    public:
        Character* operator[](size_t idx) const;
        Team();
        explicit Team(const char* teamLabel);

        Team(const Team& other);
        Team& operator=(const Team& other);
        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;
        ~Team();

        void addMember(const Character* c);
        void removeMember(const std::string& characterName);

        Character* getMember(size_t idx) const;
        void showMembers() const;
    };
}

#endif
