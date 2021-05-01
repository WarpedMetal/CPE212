#include "rogue.hpp"


Rogue::Rogue(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid) : 
        Entity(builder, inventory, uid)
{
    std::cout << Name() << " the rogue has entered the battle" << std::endl;
}

void Rogue::PickPocket(Entity * target, uint32_t itemUID)
{    
    add_item_to_inventory(target->LoseAnItem(itemUID));
}


void Rogue::Backstab(Entity* target)
{
    Attack(target, GetAgility() * 2.0, "Backstab");
}

void Rogue::Blindside(Entity * target)
{
    Attack(target, 20, "Blindside");
}

void Rogue::SurpriseStrike(Entity * target)
{
    uint32_t baseDmgVal = 15;
    if(target->MaxHP() > target->CurrentHP())
    {
        Attack(target, baseDmgVal / 2, "SurpriseStrike");       // if current hp is less than max hp, do half damage
    }
    else
    {
        Attack(target, baseDmgVal * 2, "SurpriseStrike");       // otherwise, if target is at max hp, do double damage
    }
}

void Rogue::OutputStatus() const
{
    std::cout << Class() << ": " << this->Name()
                << "\n\tCurrent HP: " << this->CurrentHP()
                << "\n\tAgility: " << this->GetAgility()
                << std::endl;
                
    PrintInventory();
}


void Rogue::WeaponAttack(Entity * target)
{
    Attack(target, 4.0, "Dagger Attack");
}


void Rogue::UseAction(Entity * target, const std::string& spellName, const std::string & args)
{
    if(spellName == "pick_pocket")
    {
        uint32_t itemUID = std::stoul(args);
        PickPocket(target, itemUID);
        return;
    }

    if(spellName == "weapon_attack")
    {
        WeaponAttack(target);
        return;
    }
    if(spellName == "backstab")
    {
        Backstab(target);
        return;
    }
    if(spellName == "blindside")
    {
        Blindside(target);
        return;
    }

    
    errorFindingAbility(spellName);

}