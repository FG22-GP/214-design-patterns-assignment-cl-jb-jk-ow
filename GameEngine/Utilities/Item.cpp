#include "Item.h"
#include <cmath>
#include <string>

#include "../Text/Text.h"

Item::Item(const char* itemName, int baseValuePerSecond, int baseCost, int costMultiplierPerOwnedItem, Text* itemText, Text* ownedText)
{
    CostText = itemText;
    OwnedText = ownedText;
    ItemName = itemName;
    BaseValuePerSecond = baseValuePerSecond;
    BaseCost = baseCost;
    CostMultiplierPerOwnedItem = costMultiplierPerOwnedItem;

    RefreshItemTexts();
}

int Item::GetItemCps()
{
    return BaseValuePerSecond * OwnedAmount * Multiplier;
}

int Item::GetItemCost()
{
    int CurrentCost = BaseCost;

    if(CostMultiplierPerOwnedItem * OwnedAmount > 0)
    {
        CurrentCost *= (CostMultiplierPerOwnedItem * OwnedAmount);
    }
    
    return CurrentCost;
}

void Item::BuyItem(int Amount)
{
    OwnedAmount += Amount;
    SetItemMultiplier();

    RefreshItemTexts();
}

//Adds 1x to the items multiplier every 20 items owned
void Item::SetItemMultiplier()
{
    float NewMultiplier = OwnedAmount/20;
    Multiplier = 1 + floor(NewMultiplier);
}

void Item::RefreshItemTexts()
{
    std::string costString = "Costs: ";
    std::string ownedString = "Owned: ";
    
    CostText->SetText(costString.append(std::to_string(GetItemCost())).c_str());
    OwnedText->SetText(ownedString.append(std::to_string(OwnedAmount)).c_str());
}
