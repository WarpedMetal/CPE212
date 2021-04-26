#include "JsonEntityBuilder.hpp"


JsonEntityBuilder::JsonEntityBuilder(const std::string & file) :
    _file(file)
{
    std::ifstream t(file);
    std::string jsonData((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

    j = json::parse(jsonData);

    auto tmp = j.find(STR_ENTITY_ID);
    if(tmp != j.end())
    {
        _entities = *tmp;
    }
    else
    {
        std::cout << "Failed to find entities" << std::endl;
        exit(-1);
    }
    
    
    tmp = j.find(STR_ITEM_ID);
    if(tmp != j.end())
    {
        _items = *tmp;
    }
    else
    {
        std::cout << "Failed to find items.   Exiting" << std::endl;
        exit(-1);
    }    
}


nlohmann::json::value_type* JsonEntityBuilder::GetItemFromID(const std::string & item, uint32_t id)
{
    for(auto & entity : _entities)
    {
        auto uidStr = entity.find(item);
        if(uidStr != entity.end())
        {
            if(*uidStr == id)
            {
                return &entity;
            }
        }
    }    

    return nullptr;
}


EntityBuilder JsonEntityBuilder::BuildEntity(uint32_t uid)
{
    EntityBuilder entity;
    json::value_type *myItem = GetItemFromID(STR_UID, uid);
    if(myItem == nullptr)
    {
        return EntityBuilder{};
    }

    auto itemFound = *myItem;

    if(itemFound.contains(STR_NAME))
    {
        entity.name = itemFound[STR_NAME];
    }
    if(itemFound.contains(STR_RACE))
    {
        entity.race = itemFound[STR_RACE];
    }
    if(itemFound.contains(STR_HP))
    {
        entity.hp = itemFound[STR_HP];
    }
    if(itemFound.contains(STR_CLASS))
    {
        entity.Class = itemFound[STR_CLASS];
    }

    if(itemFound.contains(STR_STR))
    {
        entity.strength = itemFound[STR_STR];
    }
    if(itemFound.contains(STR_AGI))
    {
        entity.agility = itemFound[STR_AGI];
    }
    if(itemFound.contains(STR_INT))
    {
        entity.intelligence = itemFound[STR_INT];
    }
    if(itemFound.contains(STR_WIS))
    {
        entity.wisdom = itemFound[STR_WIS];
    }

    if(itemFound.contains(STR_DAM))
    {
        entity.weapon_damage = itemFound[STR_DAM];
    }
    if(itemFound.contains(STR_INVENTORY))
    {
        std::vector<int> data = itemFound[STR_INVENTORY];

        for(const auto & uid : data)
        {
            entity.inventoryIDs.push_back(uid);
        }
    }

    entity.valid = true;

    return entity;
}
