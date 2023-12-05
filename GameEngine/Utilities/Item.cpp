#include "Item.h"
#include <cmath>

Item::Item(const char* itemName, int baseValuePerSecond, int baseCost, int costMultiplierPerOwnedItem)
{
    ItemName = itemName;
    BaseValuePerSecond = baseValuePerSecond;
    BaseCost = baseCost;
    CostMultiplierPerOwnedItem = costMultiplierPerOwnedItem;
}

int Item::GetItemCps()
{
    return BaseValuePerSecond * OwnedAmount * Multiplier;
}

int Item::GetItemCost()
{
    return BaseCost * (CostMultiplierPerOwnedItem * OwnedAmount);
}

void Item::BuyItem(int Amount)
{
    OwnedAmount += Amount;
    SetItemMultiplier();
}

//Adds 1x to the items multiplier every 20 items owned
void Item::SetItemMultiplier()
{
    float NewMultiplier = OwnedAmount/20;
    Multiplier = 1 + floor(NewMultiplier);
}
