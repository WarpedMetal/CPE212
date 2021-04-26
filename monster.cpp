#include "monster.hpp"

Monster::Monster(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid) : 
        Entity(builder, inventory, uid)
{
    weapon_damage = _builder.weapon_damage;

    std::cout << Name() << " the monster has entered the battle" << std::endl;
}

void Monster::WeaponAttack(Entity *target)
{
    Attack(target, this->weapon_damage, "WeaponAttack");
}

void Monster::OutputStatus() const
{
    std::cout << this->Race() << ": " << this->Name()
                << "\n\tCurrent HP: " << this->CurrentHP()
                << "\n\tHIDDEN INVENTORY"
                << std::endl;
}

void Monster::UseAction(Entity * target, const std::string& spellName, const std::string & args)
{
    if(spellName == "weapon_attack")
    {
        WeaponAttack(target);
        return;
    }
    
    errorFindingAbility(spellName);
}