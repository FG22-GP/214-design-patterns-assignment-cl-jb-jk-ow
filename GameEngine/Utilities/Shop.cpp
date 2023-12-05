#include "Shop.h"

void Shop::AddNewShopItem(Item* newItem)
{
    ShopItemMap.insert(std::make_pair(newItem->ItemName, newItem));
}

Item* Shop::GetShopItem(const char* itemName)
{
    return ShopItemMap.at(itemName);
}
