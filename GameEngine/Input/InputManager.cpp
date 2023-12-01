#include "InputManager.h"

InputManager::InputManager() {
    // Initialize key states
    keyStates = SDL_GetKeyboardState(nullptr);

    // Initialize mouse position
    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager() = default;

void InputManager::Update() {
    // Update key states
    SDL_PumpEvents();

    // Update mouse state
    SDL_GetMouseState(&mouseX, &mouseY);
}

bool InputManager::IsKeyPressed(SDL_Scancode key) const {
    return keyStates[key];
}

bool InputManager::IsMouseButtonPressed(Uint8 button) const {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
}

int InputManager::GetMouseX() const {
    return mouseX;
}

int InputManager::GetMouseY() const {
    return mouseY;
}

std::vector<int> InputManager::OnMouseClick() const {
    // Return a vector with mouse X and Y position
    return {mouseX, mouseY};
}

void InputManager::OnKeyPress(SDL_Scancode key) {
    // Set the key as pressed
    pressedKeys[key] = true;
}

void InputManager::OnKeyRelease(SDL_Scancode key) {
    // Set the key as released
    pressedKeys[key] = false;
}
