#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"
#include <iostream>

namespace seneca
{
    // Barbarian template using flexible Health, Ability, and Weapon types.
    template <typename Health_t, typename Skill_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<Health_t>
    {
        int atkBase_;
        int defBase_;
        Skill_t skill_;
        Weapon_t arsenal_[2];  // dual weapons

        // helper: compute base attack using both weapons
        int totalAttack() const noexcept
        {
            double w1 = static_cast<double>(arsenal_[0]);
            double w2 = static_cast<double>(arsenal_[1]);
            return static_cast<int>(atkBase_ + (w1 + w2) / 2.0);
        }

        // helper: compute defense
        int totalDefense() const noexcept
        {
            return defBase_;
        }

    public:
        Barbarian(const char* nm, int healthMax, int atk, int def,
                  Weapon_t firstWpn, Weapon_t secondWpn)
            : CharacterTpl<Health_t>(nm, healthMax),
              atkBase_(atk),
              defBase_(def)
        {
            arsenal_[0] = firstWpn;
            arsenal_[1] = secondWpn;
        }

        int getAttackAmnt() const override
        {
            return totalAttack();
        }

        int getDefenseAmnt() const override
        {
            return totalDefense();
        }

        Character* clone() const override
        {
            return new Barbarian<Health_t, Skill_t, Weapon_t>(*this);
        }

        void attack(Character* foe) override
        {
            if (!foe) return;

            std::cout << this->getName() << " swings at " << foe->getName() << " with brute force!\n";

            // use and modify through ability
            skill_.useAbility(this);

            int inflicted = totalAttack();
            skill_.transformDamageDealt(inflicted);

            std::cout << "    Barbarian smashes for " << inflicted << " melee damage!\n";
            foe->takeDamage(inflicted);
        }

        void takeDamage(int dmg) override
        {
            std::cout << this->getName() << " absorbs an incoming hit of " << dmg << ".\n";
            std::cout << "    Barbarian’s raw defense: " << defBase_ << "\n";

            int adjusted = dmg - defBase_;
            if (adjusted < 0) adjusted = 0;

            skill_.transformDamageReceived(adjusted);

            CharacterTpl<Health_t>::takeDamage(adjusted);
        }
    };
}

#endif // SENECA_BARBARIAN_H
