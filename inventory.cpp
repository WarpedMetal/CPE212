#include "inventory.hpp"


Inventory::~Inventory()
{

}


/// provided
void Inventory::Init(JsonItemBuilder &jsonBuilder, const std::vector<int> & uids)
{
    for(const auto & uid : uids)
    {
        _inventoryData.Insert(uid, {jsonBuilder, static_cast<uint32_t>(uid)});
    }


}

void Inventory::AddItemToInventory(const Item &item)
{
    _inventoryData.Insert(item.UID(), item);
}


Item Inventory::LootAnItem(uint32_t uid)
{
    if(_inventoryData.Contains(uid))
    {
        Item retval = _inventoryData.At(uid);
        _inventoryData.Remove(uid);
        return retval;
    }
    return Item{};
}

void Inventory::LootAnotherInventory(Inventory & inventory)
{
    Vector<uint32_t> itemKeys = inventory._inventoryData.Keys();

    for(int i = 0; i < itemKeys.Count(); i ++)
    {
        Item lootedItem = inventory._inventoryData.At(itemKeys.At(i));
        _inventoryData.Insert(lootedItem.UID(), lootedItem);
        inventory._inventoryData.Remove(itemKeys.At(i));
    }

}


bool Inventory::IsEmpty() const
{
    return _inventoryData.IsEmpty();

}


// implement
// loops through the list and calls the item to 
// print its contents though the Item::PrintData()
void Inventory::PrintInventory() const
{
    Vector<uint32_t> keys = _inventoryData.Keys();
    for(int i = 0; i < keys.Count(); i ++)
    {
        uint32_t key = keys.At(i);
        std::cout << _inventoryData.At(key) << std::endl;
    }
}
