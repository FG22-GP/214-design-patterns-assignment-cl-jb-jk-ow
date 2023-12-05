#include "Item.h"
#include <cmath>
#include <string>

#include "../Text/Text.h"

Item::Item(Transform initialTransform, const char* itemName, int baseValuePerSecond, int baseCost, int costMultiplierPerOwnedItem, Image* previewImage, Text* nameText, Text* costText, Text* ownedText) : GameObject(initialTransform)
{
    ItemName = itemName;
    BaseValuePerSecond = baseValuePerSecond;
    BaseCost = baseCost;
    CostMultiplierPerOwnedItem = costMultiplierPerOwnedItem;

    PreviewImage = previewImage;
    NameText = nameText;
    CostText = costText;
    OwnedText = ownedText;

    AddComponent(PreviewImage);
    AddComponent(NameText);
    AddComponent(CostText);
    AddComponent(OwnedText);

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
