#include "team.h"
#include <iostream>
#include <utility>

namespace seneca
{
    Team::Team() : label(""), roster(nullptr), count(0) {}

    Team::Team(const char* teamLabel) : label(teamLabel ? teamLabel : ""), roster(nullptr), count(0) {}

    void Team::cleanupRoster()
    {
        for (size_t i = 0; i < count; ++i) delete roster[i];
        delete[] roster;
        roster = nullptr;
        count = 0;
    }

    Team::Team(const Team& other) : label(other.label), roster(nullptr), count(0)
    {
        if (!other.roster) return;

        count = other.count;
        roster = new Character*[count];
        for (size_t i = 0; i < count; ++i)
            roster[i] = other.roster[i]->clone();
    }

    Team& Team::operator=(const Team& other)
    {
        if (this == &other) return *this;

        cleanupRoster();
        label = other.label;
        if (!other.roster) return *this;

        count = other.count;
        roster = new Character*[count];
        for (size_t i = 0; i < count; ++i)
            roster[i] = other.roster[i]->clone();

        return *this;
    }

    Team::Team(Team&& other) noexcept
        : label(std::move(other.label)), roster(other.roster), count(other.count)
    {
        other.roster = nullptr;
        other.count = 0;
    }

    Team& Team::operator=(Team&& other) noexcept
    {
        if (this == &other) return *this;

        cleanupRoster();
        label = std::move(other.label);
        roster = other.roster;
        count = other.count;

        other.roster = nullptr;
        other.count = 0;

        return *this;
    }

    Team::~Team() { cleanupRoster(); }

    void Team::addMember(const Character* c)
    {
        if (!c) return;

        for (size_t i = 0; i < count; ++i)
            if (roster[i]->getName() == c->getName()) return;

        Character** temp = new Character*[count + 1];
        size_t i = 0;
        for (; i < count; ++i) temp[i] = roster[i];

        temp[i] = c->clone();
        delete[] roster;
        roster = temp;
        ++count;
    }

    void Team::removeMember(const std::string& characterName)
    {
        size_t idx = count;
        size_t i = 0;
        while (i < count)
        {
            if (roster[i]->getName() == characterName)
            {
                idx = i;
                break;
            }
            ++i;
        }

        if (idx >= count) return;

        delete roster[idx];

        if (count == 1)
        {
            delete[] roster;
            roster = nullptr;
            count = 0;
            return;
        }

        Character** temp = new Character*[count - 1];
        size_t j = 0;
        for (i = 0; i < count; ++i)
        {
            if (i != idx)
            {
                temp[j++] = roster[i];
            }
        }

        delete[] roster;
        roster = temp;
        --count;
    }

    Character* Team::getMember(size_t idx) const
    {
        return (idx < count) ? roster[idx] : nullptr;
    }

    void Team::showMembers() const
    {
        if (count == 0)
        {
            std::cout << "Team is empty.\n";
            return;
        }

        std::cout << "Team: " << label << "\n";
        size_t i = 0;
        while (i < count)
        {
            std::cout << "  [" << (i + 1) << "] " << *roster[i] << "\n";
            ++i;
        }
    }
    Character* Team::operator[](size_t idx) const
    {
    return (idx < count) ? roster[idx] : nullptr;
    }

}
