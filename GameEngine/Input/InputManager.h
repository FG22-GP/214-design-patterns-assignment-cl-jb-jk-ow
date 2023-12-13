#pragma once

#include <memory>
#include <SDL.h>
#include <unordered_map>
#include <vector>

#include "../Utilities/GameState.h"
#include "../Utilities/IClickObserver.h"
#include "../Utilities/IObservable.h"

class GameObject;

class InputManager : public IObservable {
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
    std::vector<int> GetMousePos() const;

    //Get position of click
    //Will only return valid values if left click is pressed
    std::vector<int> GetClickPos() const;

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

    void AddClickable(std::shared_ptr<GameObject> clickable, std::string name);

    //IObservable
    void AddObserver(const std::string& id, std::shared_ptr<IClickObserver> observer) override;

    void RemoveObserver(const std::string& id) override;

    void NotifyObserver(const std::string& id) override;
    
    void NotifyAll() override;
    
private:
    const Uint8* keyStates;  // Array of current key states
    int mouseX, mouseY;      // Current mouse position
    int clickX, clickY;      // Coords of last click
    std::unordered_map<SDL_Scancode, bool> pressedKeys;  // Hashset to store pressed keys
    std::unordered_map<Uint8, bool> pressedMouseButtons; // Hashset to store pressed mouse buttons
    std::unordered_map<std::shared_ptr<GameObject>, std::string> clickables;
    GameState* gameState;
};

