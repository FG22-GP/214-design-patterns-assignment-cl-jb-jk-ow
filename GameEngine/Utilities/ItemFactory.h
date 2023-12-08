#pragma once

#include "GameObject.h"
#include "Item.h"
#include "Shop.h"

class TextFactory;

class ItemFactory {
public:
    static Item* CreateNewItem(const char* ItemName, TextFactory* textfactory, int BaseValuePerSecond, int BaseCost, int CostMultiplierPerOwnedItem, Vector2 ItemRenderPosition, const char* ItemImageURL, Shop* ItemShop, SDL_Renderer* Renderer);
};
