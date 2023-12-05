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
    std::ofstream file(filePath);
    
    if (file.is_open()) {
        file << std::string("AmountInBank: ") << gameState.AmountInBank << "\n";
        //TODO some sort of iterator for each field of the gamestate struct.

        // Iterate over the vector of items and save their information
        for (const auto& tuple : gameState.AutoClickers) {
            file << std::string(std::get<const char*>(tuple)) << ": " << std::get<int>(tuple) << "\n";
        }

        file.close();
        std::cout << "Game state saved successfully to: " << filePath << "\n";
    }
}

GameState SaveGameUtils::LoadGame() {
    const std::string filename = "save.txt";
    GameState gameState;

    fs::path filePath = fs::current_path() / filename;
    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Parse the line and update the GameState object
            if (line.find("AmountInBank: ") != std::string::npos) {
                gameState.AmountInBank = std::stoi(line.substr(line.find(": ") + 2));
            }
            else if(line.find(": ") != std::string::npos)
            {
                std::string itemName = line.substr(0, line.find(": "));
                int ownedAmount = std::stoi(line.substr(line.find(": ") + 2));

                //Populate the vector of tuples with info from save file
                gameState.AutoClickers.push_back(std::make_tuple(itemName.c_str(), ownedAmount));
            }
        }

        file.close();
        std::cout << "Game state loaded successfully from: " << filePath << "\n";
    }

    return gameState;
}
