#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "weapons.h"
#include <iostream>

namespace seneca
{
    // Rogue template class using two abilities and a single Dagger weapon
    template <typename Health_t, typename PrimarySkill_t, typename SecondarySkill_t>
    class Rogue : public CharacterTpl<Health_t>
    {
        int atkRating_;
        int defRating_;
        Dagger blade_;
        PrimarySkill_t primarySkill_;
        SecondarySkill_t secondarySkill_;

        // helper: total damage output considering base and dagger
        int computeAttackPower() const noexcept
        {
            double bladePower = static_cast<double>(blade_);
            // multiplier 2.0 retained, restructured expression
            return static_cast<int>(atkRating_ + bladePower * 2.0);
        }

        // helper: defense power
        int computeDefensePower() const noexcept
        {
            return defRating_;
        }

        void applyAbilitiesBeforeAttack()
        {
            primarySkill_.useAbility(this);
            secondarySkill_.useAbility(this);
        }

        void applyDamageModifiers(int& damage)
        {
            primarySkill_.transformDamageDealt(damage);
            secondarySkill_.transformDamageDealt(damage);
        }

        void applyDefenseModifiers(int& incoming)
        {
            primarySkill_.transformDamageReceived(incoming);
            secondarySkill_.transformDamageReceived(incoming);
        }

    public:
        Rogue(const char* alias, int maxHealth, int baseAtk, int baseDef)
            : CharacterTpl<Health_t>(alias, maxHealth),
              atkRating_(baseAtk),
              defRating_(baseDef)
        {}

        int getAttackAmnt() const override
        {
            return computeAttackPower();
        }

        int getDefenseAmnt() const override
        {
            return computeDefensePower();
        }

        Character* clone() const override
        {
            return new Rogue<Health_t, PrimarySkill_t, SecondarySkill_t>(*this);
        }

        void attack(Character* target) override
        {
            if (!target) return;

            std::cout << this->getName() << " darts toward " << target->getName() << "!\n";
            applyAbilitiesBeforeAttack();

            int totalDmg = computeAttackPower();
            applyDamageModifiers(totalDmg);

            std::cout << "    Rogue strikes for " << totalDmg << " precision damage!\n";
            target->takeDamage(totalDmg);
        }

        void takeDamage(int incoming) override
        {
            std::cout << this->getName() << " is targeted for " << incoming << " damage.\n";
            std::cout << "    Rogue’s agility grants " << defRating_ 
                      << " defense points. Mitigating damage...\n";

            int reduced = incoming - defRating_;
            if (reduced < 0) reduced = 0;

            applyDefenseModifiers(reduced);
            CharacterTpl<Health_t>::takeDamage(reduced);
        }
    };
}

#endif // SENECA_ROGUE_H
