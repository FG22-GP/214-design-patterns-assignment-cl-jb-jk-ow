#pragma once

class Item
{
public:
    Item(const char* itemName, int baseValuePerSecond, int baseCost, int costMultiplierPerOwnedItem);
    
    const char* ItemName;
    
    int BaseCost;
    int CostMultiplierPerOwnedItem;
    int BaseValuePerSecond;
    int Multiplier = 1;
    
    int OwnedAmount = 0;

    int GetItemCps();
    int GetItemCost();

    void BuyItem(int Amount);
    void SetItemMultiplier();
};
