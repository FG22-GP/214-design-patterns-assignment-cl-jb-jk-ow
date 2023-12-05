#pragma once
#include "GameObject.h"
#include "../Image/Image.h"

class Text;

class Item : public GameObject
{
public:
    Item(Transform initialTransform, const char* itemName, int baseValuePerSecond, int baseCost, int costMultiplierPerOwnedItem, Image* previewImage, Text* nameText, Text* costText, Text* ownedText);
    
    const char* ItemName;
    Image* PreviewImage;
    Text* NameText;
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
