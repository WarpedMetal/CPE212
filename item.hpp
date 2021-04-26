#ifndef ITEM_HPP
#define ITEM_HPP

#include "JsonItemBuilder.hpp"
#include <string>
#include <iostream>


class Item
{
public:
    Item() = default;
    Item(JsonItemBuilder &jsonBuiltItem, uint32_t uid);

    uint32_t UID() const;
    uint32_t Damage() const;
    uint32_t Armor() const;

    std::string Name() const;
    std::string Type() const;

    friend std::ostream& operator<<(std::ostream& os, const Item& item);

private:
    ItemBuilder _builder;

    uint32_t _uid = 0;
    std::string _name = "";
    std::string _type = "";

    uint32_t _damage = 0;
    uint32_t _armor = 0;

};


#endif