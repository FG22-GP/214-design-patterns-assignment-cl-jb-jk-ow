#pragma once
#include <SDL_render.h>

class Item
{
public:
    Item(const char* itemName, SDL_Texture* itemTexture, int baseValuePerSecond, int baseCost, int costMultiplierPerOwnedItem);
    
    const char* ItemName;
    SDL_Texture* ItemTexture;

    int BaseCost;
    int CostMultiplierPerOwnedItem;
    int BaseValuePerSecond;
    int Multiplier = 1;
    
    int OwnedAmount = 0;

    int GetItemCps();

    void BuyItem(int Amount);
    void SetItemMultiplier();
};
