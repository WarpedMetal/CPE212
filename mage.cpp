#include "mage.hpp"


Mage::Mage(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid) : 
    Entity(builder, inventory, uid)
{
    std::cout << Name() << " the mage has entered the battle" << std::endl;
}



void Mage::Fireball(Entity *target)
{
    Attack(target, GetIntelligence() * 1.5, "Fireball");
}

void Mage::MagicMissiles(Entity *target)
{
    Attack(target, GetIntelligence() * 0.5, "Magic Missile");
    Attack(target, GetIntelligence() * 0.5, "Magic Missile");
    Attack(target, GetIntelligence() * 0.5, "Magic Missile");
}

void Mage::OutputStatus() const
{
    std::cout << Class() << ": " << this->Name()
                << "\n\tCurrent HP: " << this->CurrentHP()
                << "\n\tIntelligence: " << this->GetIntelligence()
                << std::endl;

    PrintInventory();
}

void Mage::WeaponAttack(Entity * target)
{
    Attack(target, 4.0, "Staff Attack");
}

void Mage::UseAction(Entity * target, const std::string& spellName, const std::string & args)
{
    if(spellName == "weapon_attack")
    {
        WeaponAttack(target);
        return;
    }
    if(spellName == "fireball")
    {
        Fireball(target);
        return;
    }
    if(spellName == "magic_missile")
    {
        MagicMissiles(target);
        return;
    }
    errorFindingAbility(spellName);
}