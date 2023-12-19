#include "GameState.h"


int GameState::CubeCount = 0;
GameState* GameState::Instance = nullptr;

void GameState::UpdateItem(Item* item)
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
    AutoClickers.emplace_back(item->ItemName, item->OwnedAmount);
}

std::shared_ptr<Item> GameState::FindItemByName(const std::vector<std::shared_ptr<Item>> items, std::string name) {
    for (std::shared_ptr<Item> item : items) {
        if (item->ItemName == name) {
            return item;
        }
    }
    return nullptr; // Item not found
}

void GameState::SetItemValuesFromSave(std::vector<std::shared_ptr<Item>> items)
{
    for (auto autoClicker : AutoClickers) {
        const std::string itemName = std::get<0>(autoClicker);
        const int ownedAmount = std::get<1>(autoClicker);

        //TODO: check if we can remove raw ptr
        // Find the corresponding item
        Item* item = FindItemByName(items, itemName).get();

        if (item) {
            item->OwnedAmount = ownedAmount;
            item->RefreshItemTexts();
        }
    }
}

void GameState::AddToCubeCount(int amount)
{
    CubeCount += amount;
}