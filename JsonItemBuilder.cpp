#include "JsonItemBuilder.hpp"


JsonItemBuilder::JsonItemBuilder(const std::string & fileName) : 
    _file(fileName)
{
    std::ifstream t(fileName);
    std::string jsonData((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

    j = json::parse(jsonData);
   
    
    auto tmp = j.find(STR_ITEM_ID);
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

nlohmann::json::value_type* JsonItemBuilder::GetItemFromID(const std::string & item, uint32_t id)
{
    for(auto & entity : _items)
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


ItemBuilder JsonItemBuilder::BuildItem(uint32_t uid)
{
    ItemBuilder item;
    json::value_type *myItem = GetItemFromID(STR_UID, uid);
    if(myItem == nullptr)
    {
        return ItemBuilder{};
    }

    auto itemFound = *myItem;


    if(itemFound.contains(STR_UID))
    {
        item.uid = itemFound[STR_UID];
    }
    if(itemFound.contains(STR_NAME))
    {
        item.name = itemFound[STR_NAME];
    }
    if(itemFound.contains(STR_TYPE))
    {
        item.type = itemFound[STR_TYPE];
    }
    if(itemFound.contains(STR_DAMAGE))
    {
        item.damage = itemFound[STR_DAMAGE];
    }
    if(itemFound.contains(STR_ARMOR))
    {
        item.armor = itemFound[STR_ARMOR];
    }

    item.valid = true;

    return item;
}