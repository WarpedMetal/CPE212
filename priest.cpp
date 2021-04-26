#include "priest.hpp"


Priest::Priest(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid) : 
    Entity(builder, inventory, uid)
{
    std::cout << Name() << " the priest has entered the battle" << std::endl;
}


void Priest::Smite(Entity * target)
{
    Attack(target, GetWisdom() * 0.5, "Smite");
}


void Priest::GreaterHeal(Entity *target)
{
    Heal(target, GetWisdom() * 2.0, "Greater Heal");
}


void Priest::OutputStatus() const
{
    std::cout << Class() << ": " << this->Name()
                << "\n\tCurrent HP: " << this->CurrentHP()
                << "\n\tWisdom: " << this->GetWisdom()
                << std::endl;
                
    PrintInventory();
}

void Priest::WeaponAttack(Entity * target)
{
    Attack(target, 4.0, "Mace Attack");
}

void Priest::UseAction(Entity * target, const std::string& spellName, const std::string & args)
{
    if(spellName == "weapon_attack")
    {
        WeaponAttack(target);
        return;
    }
    if(spellName == "smite")
    {
        Smite(target);
        return;
    }
    if(spellName == "greater_heal")
    {
        GreaterHeal(target);
        return;
    }
    errorFindingAbility(spellName);

}