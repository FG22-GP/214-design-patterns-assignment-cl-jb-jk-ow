#include "SaveGameUtils.h"
#include "iostream"
#include "fstream"
#include "string"
#include "filesystem"
#include "GameState.h"

namespace fs = std::filesystem;

void SaveGameUtils::SaveGame(const GameState& gameState) {
    const std::string filename = "save.txt";
    fs::path filePath = fs::current_path() / filename;
    std::ofstream file(filePath, std::ios::out | std::ios::binary);
    
    if (file.is_open()) {
        file << std::string("CubeCount: ") << GameState::CubeCount << "\n";

        // Iterate over the vector of items and save their information
        for (const auto& tuple : gameState.AutoClickers) {
            file << std::get<0>(tuple) << ": " << std::get<1>(tuple) << "\n";
        }

        file.close();
        std::cout << "Game state saved successfully to: " << filePath << "\n";
    }
}

GameState SaveGameUtils::LoadGame(std::vector<std::shared_ptr<Item>>& items) {
    std::ifstream stream;
    const std::string filename = "save.txt";

    fs::path filePath = fs::current_path() / filename;
    stream.open(filePath, std::ifstream::in | std::ios::binary);
    
    if (stream.is_open()) {
        GameState gameState;
        std::string line;
        while (std::getline(stream, line)) {
            // Parse the line and update the GameState object
            if (line.find("CubeCount: ") != std::string::npos) {
                GameState::CubeCount = std::stoi(line.substr(line.find(": ") + 2));
            }
            else if(line.find(": "))
            {
                // Split the line into item name and owned amount
                std::string itemNameStr = line.substr(0, line.find(": "));
                const char* itemName = itemNameStr.c_str();
                int ownedAmount = std::stoi(line.substr(line.find(": ") + 2));

                //TODO: check if we can remove raw ptr
                // Populate the vector of tuples with info from save file
                Item* item = gameState.FindItemByName(items, itemName).get();

                if (item) {
                    gameState.AutoClickers.emplace_back(itemName, ownedAmount);
                }
            }
        }
        GameState::Instance = &gameState;
        stream.close();
        std::cout << "Game state loaded successfully from: " << filePath << "\n";
        return gameState;
    }
    return {};
}
