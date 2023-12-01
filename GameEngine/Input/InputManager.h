#pragma once

#include <SDL.h>
#include <unordered_map>
#include <vector>

class InputManager {
public:
    // Constructor
    InputManager();

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

    // Handle mouse click
    std::vector<int> OnMouseClick() const;

    // Handle key press
    void OnKeyPress(SDL_Scancode key);

    // Handle key release
    void OnKeyRelease(SDL_Scancode key);

private:
    const Uint8* keyStates;  // Array of current key states
    int mouseX, mouseY;      // Current mouse position
    std::unordered_map<SDL_Scancode, bool> pressedKeys;  // Hashset to store pressed keys
};

