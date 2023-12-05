#pragma once
#include <unordered_map>
#include <vector>

#include "Item.h"

struct GameState
{
    GameState() : AmountInBank(0), AutoClickers() {}
    
    int AmountInBank;
    std::vector<std::tuple<const char*, int>> AutoClickers;
    // Add new fields for each building

    void AddItem(Item item);
};

inline void GameState::AddItem(Item item)
{
    AutoClickers.push_back(std::make_tuple(item.ItemName, item.OwnedAmount));
}
