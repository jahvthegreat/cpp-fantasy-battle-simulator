#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
#include <iostream>

namespace seneca {

// Generic character implementation whose HealthType controls how damage is handled.
template <typename HealthType>
class CharacterTpl : public Character {
    int m_healthMax;
    HealthType m_health;

public:
    CharacterTpl(const char* name, int healthMax)
        : Character(name), m_healthMax(healthMax > 0 ? healthMax : 1), m_health{} {
        m_health = m_healthMax;
    }

    void takeDamage(int damage) override {
        if (damage < 0) damage = 0;
        m_health -= damage;
        if (getHealth() < 0) m_health = 0;
        if (getHealth() > m_healthMax) m_health = m_healthMax;

        if (getHealth() <= 0) {
            std::cout << "    " << getName() << " has been defeated!\n";
        } else {
            std::cout << "    " << getName() << " took " << damage
                      << " damage, " << getHealth() << " health remaining.\n";
        }
    }

    int getHealth() const override {
        return static_cast<int>(m_health);
    }

    int getHealthMax() const override {
        return m_healthMax;
    }

    void setHealth(int health) override {
        if (health < 0) health = 0;
        if (health > m_healthMax) health = m_healthMax;
        m_health = health;
    }

    void setHealthMax(int health) override {
        m_healthMax = health > 0 ? health : 1;
        m_health = m_healthMax;
    }
};

} // namespace seneca

#endif // SENECA_CHARACTERTPL_H
