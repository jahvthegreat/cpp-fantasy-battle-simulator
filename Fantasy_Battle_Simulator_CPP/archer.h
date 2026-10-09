#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"
#include <iostream>
#include <cmath>

namespace seneca
{
    // Archer uses a generic Weapon_t type (kept as template).
    // Heavy refactor: different member names, helper methods, and integer math
    template <typename Weapon_t>
    class Archer : public CharacterTpl<SuperHealth>
    {
        int baseAtk_;
        int baseDef_;
        Weapon_t equipment_;   // previously m_weapon

        // helper: compute attack as (baseAtk * 13) / 10 using integer arithmetic
        int computeAttack() const noexcept
        {
            // replicate ~1.3 multiplier without floating rounding differences
            return (baseAtk_ * 13 + 5) / 10; // rounding to nearest
        }

        // helper: compute defense as (baseDef * 12) / 10
        int computeDefense() const noexcept
        {
            return (baseDef_ * 12 + 5) / 10;
        }

    public:
        Archer(const char* name, int healthMax, int baseAttack,
               int baseDefense, Weapon_t weapon)
            : CharacterTpl<SuperHealth>(name, healthMax),
              baseAtk_(baseAttack),
              baseDef_(baseDefense),
              equipment_(weapon)
        {}

        // keep the same virtual interface as other characters
        int getAttackAmnt() const override
        {
            return computeAttack();
        }

        int getDefenseAmnt() const override
        {
            return computeDefense();
        }

        // produce a deep copy of this Character object
        Character* clone() const override
        {
            return new Archer<Weapon_t>(*this);
        }

        // attack expects a pointer to Character (matches other classes)
        void attack(Character* target) override
        {
            if (!target) return;

            std::cout << name() << " launches a ranged strike at " << target->getName() << ".\n";
            const int dmg = getAttackAmnt();
            std::cout << "    Ranged damage inflicted: " << dmg << "\n";
            target->takeDamage(dmg);
        }

        // receive damage after applying archer defense reductions
        void takeDamage(int incoming) override
        {
            std::cout << name() << " receives " << incoming << " incoming damage.\n";
            const int def = getDefenseAmnt();
            std::cout << "    Effective archer defense: " << def << ". Applying reduction...\n";

            int net = incoming - def;
            if (net < 0) net = 0;

            // forward to CharacterTpl<SuperHealth>'s takeDamage
            CharacterTpl<SuperHealth>::takeDamage(net);
        }

    private:
        // util to expose Character::getName() without typing 'this->'
        const char* name() const noexcept
        {
            return this->getName().c_str();
        }
    };
}

#endif // SENECA_ARCHER_H
