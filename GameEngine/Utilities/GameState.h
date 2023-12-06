#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "Item.h"
class Item;

struct GameState
{
    GameState() : AmountInBank(0), AutoClickers() {}
    
    int AmountInBank;
    std::vector<std::tuple<std::string, int>> AutoClickers;

    Item* FindItemByName(const std::vector<Item*> items, std::string name);

    void UpdateItem(Item* item);

    void SetItemValuesFromSave(std::vector<Item*> items);
};

inline void GameState::UpdateItem(Item* item)
{
    for (auto& autoClicker : AutoClickers) {
        std::string itemName = std::get<0>(autoClicker);

        // Check if the item names match
        if (itemName == item->ItemName) {
            // Update the tuple's int value with item's OwnedAmount
            std::get<int>(autoClicker) = item->OwnedAmount;
            return;
        }
    }
    // If the item is not present, add it to the AutoClickers vector
    AutoClickers.push_back(std::make_tuple(item->ItemName, item->OwnedAmount));
    printf("Added new item: %s\n", item->ItemName);
}

inline Item* GameState::FindItemByName(const std::vector<Item*> items, std::string name) {
    for (Item* item : items) {
        if (item->ItemName == name) {
            return item;
        }
    }
    return nullptr; // Item not found
}

inline void GameState::SetItemValuesFromSave(std::vector<Item*> items)
{
    for (auto autoClicker : AutoClickers) {
        const std::string itemName = std::get<0>(autoClicker);
        const int ownedAmount = std::get<1>(autoClicker);

        // Find the corresponding item
        Item* item = FindItemByName(items, itemName);

        if (item) {
            item->OwnedAmount = ownedAmount;
            item->RefreshItemTexts();
        }
    }
}

