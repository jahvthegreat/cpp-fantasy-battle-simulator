#include "guild.h"
#include <iostream>
#include <utility>

namespace seneca
{
    Guild::Guild() : m_label(""), m_list(nullptr), m_count(0) {}

    Guild::Guild(const char* label) : m_label(label ? label : ""), m_list(nullptr), m_count(0) {}

    Guild::Guild(const Guild& src) : m_label(src.m_label), m_list(nullptr), m_count(0)
    {
        if (src.m_list)
        {
            m_count = src.m_count;
            m_list = new Character*[m_count];
            for (size_t i = 0; i < m_count; ++i)
                m_list[i] = src.m_list[i];
        }
    }

    Guild& Guild::operator=(const Guild& src)
    {
        if (this != &src)
        {
            delete[] m_list;
            m_label = src.m_label;
            m_count = src.m_count;

            if (src.m_list)
            {
                m_list = new Character*[m_count];
                for (size_t i = 0; i < m_count; ++i)
                    m_list[i] = src.m_list[i];
            }
            else
            {
                m_list = nullptr;
            }
        }
        return *this;
    }

    Guild::Guild(Guild&& src) noexcept
        : m_label(std::move(src.m_label)), m_list(src.m_list), m_count(src.m_count)
    {
        src.m_list = nullptr;
        src.m_count = 0;
    }

    Guild& Guild::operator=(Guild&& src) noexcept
    {
        if (this != &src)
        {
            delete[] m_list;
            m_label = std::move(src.m_label);
            m_list = src.m_list;
            m_count = src.m_count;

            src.m_list = nullptr;
            src.m_count = 0;
        }
        return *this;
    }

    Guild::~Guild()
    {
        delete[] m_list;  // deletes only array, not members
    }

    void Guild::addMember(Character* p)
    {
        if (!p) return;

        for (size_t i = 0; i < m_count; ++i)
        {
            if (m_list[i] == p)
                return; // already in guild
        }

        p->setHealthMax(p->getHealthMax() + 300);

        Character** newList = new Character*[m_count + 1];
        for (size_t i = 0; i < m_count; ++i)
            newList[i] = m_list[i];

        newList[m_count] = p;
        delete[] m_list;
        m_list = newList;
        ++m_count;
    }

    void Guild::removeMember(const std::string& name)
    {
        if (m_count == 0) return;

        size_t pos = m_count;
        for (size_t i = 0; i < m_count; ++i)
        {
            if (m_list[i]->getName() == name)
            {
                pos = i;
                break;
            }
        }

        if (pos >= m_count) return;

        m_list[pos]->setHealthMax(m_list[pos]->getHealthMax() - 300);

        Character** newList = nullptr;
        if (m_count > 1)
        {
            newList = new Character*[m_count - 1];
            for (size_t i = 0, j = 0; i < m_count; ++i)
            {
                if (i != pos)
                    newList[j++] = m_list[i];
            }
        }

        delete[] m_list;
        m_list = newList;
        --m_count;
    }

    Character* Guild::operator[](size_t index) const
    {
        return (index < m_count) ? m_list[index] : nullptr;
    }

    void Guild::showMembers() const
    {
        if (m_label.empty())
        {
            std::cout << "No active guild.\n";
            return;
        }

        std::cout << "[Guild] " << m_label << "\n";
        for (size_t i = 0; i < m_count; ++i)
        {
            if (m_list[i])
                std::cout << "   " << (i + 1) << ". " << *m_list[i] << "\n";
        }
    }
}
