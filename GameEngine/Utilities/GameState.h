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

    void AddItem(Item* item);

    Item* FindItemByName(const std::vector<Item*>& items, const char* name);

    void UpdateItem(Item* item);
};

inline void GameState::AddItem(Item* item)
{
    AutoClickers.push_back(std::make_tuple(item->ItemName, item->OwnedAmount));
}

inline void GameState::UpdateItem(Item* item)
{
    for (auto& autoClicker : AutoClickers) {
        const char* itemName = std::get<const char*>(autoClicker);

        // Check if the item names match
        if (strcmp(itemName, item->ItemName) == 0) {
            // Update the tuple's int value with item's OwnedAmount
            std::get<int>(autoClicker) = item->OwnedAmount;
            printf("Updated existing item: %s\n", itemName);
            return;
        }
    }
    // If the item is not present, add it to the AutoClickers vector
    //AutoClickers.push_back(std::make_tuple(item->ItemName, item->OwnedAmount));
    printf("Added new item: %s\n", item->ItemName);
}

inline Item* FindItemByName(const std::vector<Item*>& items, const char* name) {
    for (Item* item : items) {
        if (strcmp(item->ItemName, name) == 0) {
            return item;
        }
    }
    return nullptr; // Item not found
}
