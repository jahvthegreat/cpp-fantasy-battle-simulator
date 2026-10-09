#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <string>
#include "character.h"

namespace seneca
{
    class Guild
    {
        std::string m_label{};      // formerly m_name
        Character** m_list{nullptr}; // formerly m_members
        size_t m_count{0};           // formerly m_size

    public:
        Guild();
        explicit Guild(const char* label);

        // rule of five
        Guild(const Guild& src);
        Guild& operator=(const Guild& src);
        Guild(Guild&& src) noexcept;
        Guild& operator=(Guild&& src) noexcept;

        ~Guild();

        // core operations
        void addMember(Character* p);
        void removeMember(const std::string& name);

        // element access
        Character* operator[](size_t index) const;

        // display info
        void showMembers() const;
    };
}

#endif // SENECA_GUILD_H
