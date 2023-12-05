#pragma once

class Text;

class Item
{
public:
    Item(const char* itemName, int baseValuePerSecond, int baseCost, int costMultiplierPerOwnedItem, Text* costText, Text* ownedText);
    
    const char* ItemName;
    Text* CostText;
    Text* OwnedText;
    
    int BaseCost;
    int CostMultiplierPerOwnedItem;
    int BaseValuePerSecond;
    int Multiplier = 1;
    
    int OwnedAmount = 0;

    int GetItemCps();
    int GetItemCost();

    void BuyItem(int Amount);
    void SetItemMultiplier();

private:
    void RefreshItemTexts();
};
