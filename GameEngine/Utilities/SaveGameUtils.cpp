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
        //TODO some sort od iterator for each field of the gamestate struct.

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
            //Will need to add more fields here as well
        }

        file.close();
        std::cout << "Game state loaded successfully from: " << filePath << "\n";
    }

    return gameState;
}
