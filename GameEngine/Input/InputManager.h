#pragma once

#include <SDL.h>
#include <unordered_map>
#include <vector>

#include "../Utilities/GameState.h"
#include "../Utilities/IClickObserver.h"

class GameObject;

using namespace std;

class InputManager {
public:
    // Constructor
    InputManager(GameState* gs);

    // Destructor
    ~InputManager();

    // Update the input manager, called once per frame
    void Update();

    // Check if a key is currently pressed
    bool IsKeyPressed(SDL_Scancode key) const;

    // Check if a mouse button is currently pressed
    bool IsMouseButtonPressed(Uint8 button) const;

    // Get the X position of the mouse
    int GetMouseX() const;

    // Get the Y position of the mouse
    int GetMouseY() const;

    // Get current mouse position
    vector<int> GetMousePos() const;

    //Get position of click
    //Will only return valid values if left click is pressed
    vector<int> GetClickPos() const;

    // Handle key press
    void OnKeyPress(SDL_Scancode key);

    // Handle key release
    void OnKeyRelease(SDL_Scancode key);

    // Handle mouse button press
    void OnMouseButtonPress(Uint8 button);

    // Handle mouse button release
    void OnMouseButtonRelease(Uint8 button);

    void HandleItemClick(GameState* gameState);

    void HandleCubeClick(GameState* gameState);

    void HandleSaveClick(GameState* gameState);

    void AddClickable(GameObject* clickable, std::string name);

    void AddObserver(IClickObserver* observer);
    
private:
    const Uint8* keyStates;  // Array of current key states
    int mouseX, mouseY;      // Current mouse position
    int clickX, clickY;      // Coords of last click
    unordered_map<SDL_Scancode, bool> pressedKeys;  // Hashset to store pressed keys
    unordered_map<Uint8, bool> pressedMouseButtons; // Hashset to store pressed mouse buttons
    unordered_map<GameObject*, std::string> clickables;
    GameState* gameState;
    std::vector<IClickObserver*> observers;
};

