#include "item.hpp"

Item::Item(JsonItemBuilder &jsonBuiltItem, uint32_t uid)
{
    _builder = jsonBuiltItem.BuildItem(uid);

    _uid = uid;
    _name = _builder.name;
    _type = _builder.type;
    _damage = _builder.damage;
    _armor = _builder.armor;
}


uint32_t Item::UID() const
{
    return _uid;
}

uint32_t Item::Damage() const
{
    return _damage;
}

uint32_t Item::Armor() const
{
    return _armor;
}

std::string Item::Name() const
{
    return _name;
}

std::string Item::Type() const 
{
    return _type;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << "[" << item._name << "]: \n"
              << "\tType : " << item._type
              << "\n\tArmor: " << item._armor
              << "\n\tDamage: " << item._damage 
              << std::endl;


    return os;
}