#pragma once

#include "GameState.h"

class SaveGameUtils
{
public:
    static void SaveGame(const GameState& gameState);
    
    static GameState LoadGame();
};
