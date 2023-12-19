#pragma once

#include <memory>
#include "GameState.h"

class SaveGameUtils
{
public:
    static void SaveGame(const GameState& gameState);
    
    static GameState LoadGame(std::vector<std::shared_ptr<Item>>& items);
};
