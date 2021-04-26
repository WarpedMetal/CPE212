#include "warrior.hpp"


Warrior::Warrior(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid) :
    Entity(builder, inventory, uid)
{
    std::cout << Name() << " the warrior has entered the battle" << std::endl;
}


void Warrior::Strike(Entity * target)
{
    Attack(target, GetStrength() * 0.5, "Strike");
}

void Warrior::ShieldSmash(Entity * target)
{
    Attack(target, GetStrength() * 2.0, "Shield Smash");
}

void Warrior::OutputStatus() const
{
    std::cout << Class() << ": " << this->Name()
                << "\n\tCurrent HP: " << this->CurrentHP()
                << "\n\tStrength: " << this->GetStrength()
                << std::endl;
                
    PrintInventory();
}

void Warrior::WeaponAttack(Entity * target)
{
    Attack(target, 4.0, "Slash");
}

void Warrior::UseAction(Entity * target, const std::string& spellName, const std::string & args)
{
    if(spellName == "weapon_attack")
    {
        WeaponAttack(target);
        return;
    }
    if(spellName == "strike")
    {
        Strike(target);
        return;
    }
    if(spellName == "shield_smash")
    {
        ShieldSmash(target);
        return;
    }
    errorFindingAbility(spellName);

}