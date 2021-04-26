#ifndef JSONITEMBUILDER_HPP
#define JSONITEMBUILDER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"


struct ItemBuilder
{
    bool valid = false;

    uint32_t uid = 0;
    
    std::string name = "";
    std::string type = "";

    uint32_t damage = 0;
    uint32_t armor = 0;
};



class JsonItemBuilder
{
public:
    JsonItemBuilder(const std::string & fileName);

    ItemBuilder BuildItem(uint32_t uid);


private:

    nlohmann::json::value_type* GetItemFromID(const std::string & item, uint32_t id);

    const std::string STR_ITEM_ID = "items";

    const std::string STR_UID = "UID";
    const std::string STR_NAME = "name";
    const std::string STR_TYPE = "type";
    const std::string STR_DAMAGE = "damage";
    const std::string STR_ARMOR = "armor value";

    using json = nlohmann::json;
    std::string _file;
    json j;
    json _items;

};


#endif