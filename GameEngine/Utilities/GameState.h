#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "Item.h"


struct GameState
{
    GameState() = default;
    
    static int CubeCount;
    
    std::vector<std::tuple<std::string, int>> AutoClickers;

    std::shared_ptr<Item> FindItemByName(const std::vector<std::shared_ptr<Item>> items, std::string name);

    void UpdateItem(Item* item);

    void SetItemValuesFromSave(std::vector<std::shared_ptr<Item>> items);

    static void AddToCubeCount(int amount);

    static GameState* Instance;
};



