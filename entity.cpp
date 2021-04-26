#include "entity.hpp"


Entity::Entity(JsonEntityBuilder & builder, JsonItemBuilder & inventory, uint32_t uid) 
{
    _builder = builder.BuildEntity(uid);

    _uid = uid;
    _name = _builder.name;
    _hp = _builder.hp;
    _race = _builder.race;
    _maxHP = _hp;
    _strength = _builder.strength;
    _intelligence = _builder.intelligence;
    _agility = _builder.agility;
    _wisdom = _builder.wisdom;
    _class = _builder.Class;

    _inventory.Init(inventory, _builder.inventoryIDs);
}

Entity::~Entity()
{
}


// implement
// prints the inventory of this entity
void Entity::PrintInventory() const
{
    _inventory.PrintInventory();
}

// implement
// removes an item from the inventory of this entity
// based on the UID passed to this funciton.
Item Entity::LoseAnItem(uint32_t uid)
{
    return _inventory.LootAnItem(uid);
}

// implement
// 
bool Entity::HasItemsInInventory() const
{
    return !_inventory.IsEmpty();
}

// implement
// this will loop through the targets inventory
// and add one item at a time to this Entity's inventory
//
// entity is assumed to never be null, 
// you do not have to check for this.
void Entity::LootAnEntity(Entity *target)
{
    _inventory.LootAnotherInventory(target->_inventory);
}


// implement
// if item passed is null, do nothing.
void Entity::add_item_to_inventory(const Item & item)
{
    announce_item_loot(item);
    _inventory.AddItemToInventory(item);
}

uint32_t Entity::CurrentHP() const
{
    return _hp;
}

bool Entity::IsAlive() const
{
    return _hp != 0;
}

std::string Entity::Name() const
{
    return _name;
}

std::string Entity::Class() const
{
    return _class;
}

void Entity::Attack(Entity *target, uint32_t amount, const std::string &attackName)
{
    std::cout << this->Name() << " uses " << attackName << " on target "
              << target->Name() << " dealing " << amount << " damage."
              << std::endl;
    target->take_damage(amount);
}

void Entity::Heal(Entity *target, uint32_t amount, const std::string & healName)
{
    std::cout << this->Name() << " uses " << healName << " on target "
              << target->Name() << " healing for " << amount
              << std::endl;
    target->take_healing(amount);
}

void Entity::take_damage(uint32_t amount)
{
    if(_hp < amount)
    {
        _hp = 0;
        std::cout << Name() << " dies" << std::endl;
        return;
    }
    _hp -= amount;
}

void Entity::take_healing(uint32_t amount)
{
    if(_maxHP < _hp + amount)
    {
        _hp = _maxHP;
        return;
    }
    _hp += amount;
}

void Entity::announce_item_loot(const Item & item)
{
    std::cout << Name() << " has looted an item: " << item.Name() << std::endl;
}

void Entity::errorFindingAbility(const std::string& spellName)
{
    std::cout << _class << " encountered an error trying to use spell: " 
              << spellName << std::endl;
}

std::string Entity::Race() const
{
    return _race;
}

uint32_t Entity::GetStrength() const 
{
    return _strength;
}

uint32_t Entity::GetIntelligence() const
{
    return _intelligence;
}

uint32_t Entity::GetAgility() const
{
    return _agility;
}

uint32_t Entity::GetWisdom() const
{
    return _wisdom;
}

uint32_t Entity::UID() const
{
    return _uid;
}
