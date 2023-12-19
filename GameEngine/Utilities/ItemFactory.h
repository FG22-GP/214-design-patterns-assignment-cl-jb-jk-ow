#pragma once

#include <memory>

#include "GameObject.h"
#include "Item.h"
#include "Shop.h"

class TextFactory;

class ItemFactory {
public:
    static Item* CreateNewItem(const char* ItemName, std::shared_ptr<TextFactory>, int BaseValuePerSecond, int BaseCost, int CostMultiplierPerOwnedItem, Vector2 ItemRenderPosition, const char* ItemImageURL, std::shared_ptr<Shop> ItemShop, SDL_Renderer* Renderer);
};
