#ifndef JSONENTITYBUILDER_HPP
#define JSONENTITYBUILDER_HPP

#include <string>
#include <iostream>
#include <stdint.h>
#include <fstream>

#include "json.hpp"


struct EntityBuilder
{
    std::string name;
    std::string race;
    std::string Class;
    
    uint32_t hp;
    uint32_t strength;
    uint32_t agility;
    uint32_t intelligence;
    uint32_t wisdom;

    uint32_t weapon_damage;

    bool valid = false;

    std::vector<int> inventoryIDs;
};



class JsonEntityBuilder
{

    using json = nlohmann::json;
    std::string _file;
    json j;
    json _entities;
    json _items;

    
    const std::string STR_ITEM_ID = "items";
    const std::string STR_ENTITY_ID = "entities";

    const std::string STR_CLASS = "class";
    const std::string STR_NAME = "Name";
    const std::string STR_RACE = "race";
    const std::string STR_HP = "hp";
    const std::string STR_STR = "strength";
    const std::string STR_AGI = "agility";
    const std::string STR_INT = "intelligence";
    const std::string STR_WIS = "wisdom";
    const std::string STR_DAM = "weapon_damage";
    const std::string STR_UID = "UID";
    const std::string STR_INVENTORY = "inventory";


    json::value_type* GetItemFromID(const std::string & item, uint32_t id);

public:

    JsonEntityBuilder(const std::string & file);

    EntityBuilder BuildEntity(uint32_t uid);
};

#endif // JSONENTITYBUILDER_HPP