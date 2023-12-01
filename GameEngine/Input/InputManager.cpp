#include "InputManager.h"

using namespace std;

InputManager::InputManager() {
    // Initialize key states
    keyStates = SDL_GetKeyboardState(nullptr);

    // Initialize mouse position
    mouseX = 0;
    mouseY = 0;

    // Initialize click pos outside game window
    clickX = -1;
    clickY = -1;
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

vector<int> InputManager::GetMousePos() const {
    return {mouseX, mouseY};
}

vector<int> InputManager::GetClickPos() const
{
    return {clickX, clickY};
}

void InputManager::OnMouseButtonPress(Uint8 button)
{
    pressedMouseButtons[button] = true;
    // Set click pos once
    clickX = mouseX;
    clickY = mouseY;
}

void InputManager::OnMouseButtonRelease(Uint8 button)
{
    pressedMouseButtons[button] = false;
    // Reset click pos so that it's not used without user input
    clickX = -1;
    clickY = -1;
}

void InputManager::OnKeyPress(SDL_Scancode key) {
    pressedKeys[key] = true;
}

void InputManager::OnKeyRelease(SDL_Scancode key) {
    pressedKeys[key] = false;
}
