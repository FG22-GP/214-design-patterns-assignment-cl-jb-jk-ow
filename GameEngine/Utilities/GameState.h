#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "Item.h"

struct GameState
{
    GameState() : AmountInBank(0), AutoClickers() {}
    
    int AmountInBank;
    std::vector<std::tuple<std::string, int>> AutoClickers;

    void AddItem(Item* item);

    Item* FindItemByName(const std::vector<Item*>& items, std::string name);

    void UpdateItem(Item* item);
};

inline void GameState::UpdateItem(Item* item)
{
    for (auto& autoClicker : AutoClickers) {
        std::string itemName = std::get<0>(autoClicker);

        // Check if the item names match
        if (itemName == item->ItemName) {
            // Update the tuple's int value with item's OwnedAmount
            std::get<int>(autoClicker) = item->OwnedAmount;
            printf("Updated existing item: %s\n", itemName);
            return;
        }
    }
    // If the item is not present, add it to the AutoClickers vector
    AutoClickers.push_back(std::make_tuple(item->ItemName, item->OwnedAmount));
    printf("Added new item: %s\n", item->ItemName);
}

inline Item* FindItemByName(const std::vector<Item*>& items, std::string name) {
    for (Item* item : items) {
        if (item->ItemName == name) {
            return item;
        }
    }
    return nullptr; // Item not found
}
