#pragma once
#include <unordered_map>

#include "Item.h"

class Shop
{
public:
    std::unordered_map<const char*, Item*> ShopItemMap;

    void AddNewShopItem(Item* newItem);
    Item* GetShopItem(const char* itemName);
};
