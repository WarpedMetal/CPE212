#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <stdint.h>

#include <iostream>

#include "inventory.hpp"
#include "JsonEntityBuilder.hpp"
#include "JsonItemBuilder.hpp"

class Entity
{
private:
    
    uint32_t _uid;
    uint32_t _maxHP;
    uint32_t _hp;

    uint32_t _strength;
    uint32_t _agility;
    uint32_t _intelligence;
    uint32_t _wisdom;

    std::string _name;
    std::string _race;
    std::string _class;



// protected to allow access going up the inheritance tree.
protected:
    EntityBuilder _builder;
    Inventory _inventory;

    void errorFindingAbility(const std::string & spellName);

    uint32_t GetStrength() const;
    uint32_t GetAgility() const;
    uint32_t GetIntelligence() const;
    uint32_t GetWisdom() const;

    void announce_item_loot(const Item & item);

    void take_damage(uint32_t amount);
    void take_healing(uint32_t amount);
    void check_for_loot(Entity * target);
    void add_item_to_inventory(const Item & item);

    void Attack(Entity * target, uint32_t amount, const std::string &attackName);
    void Heal(Entity *target, uint32_t amount, const std::string &healName);

public:

    Entity(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid);
    virtual ~Entity();

    uint32_t CurrentHP() const;
    bool IsAlive() const;
    std::string Name() const;
    std::string Race() const;
    std::string Class() const;
    uint32_t UID() const;

    void PrintInventory() const;
    bool HasItemsInInventory() const;
    void LootAnEntity(Entity *target);
    Item LoseAnItem(uint32_t uid);

    // provided
    virtual void OutputStatus() const = 0;
    virtual void WeaponAttack(Entity * target) = 0;

    virtual void UseAction(Entity * target, const std::string& spellName, const std::string & args) = 0;
    
};


#endif // ENTITY_HPP