#include "InputManager.h"

#include "../Image/Image.h"
#include "../Text/Text.h"
#include "../Utilities/GameObject.h"
#include "../Utilities/Intersection.h"
#include "../Utilities/GameState.h"
#include "../Utilities/Item.h"
#include "../Utilities/MathUtils.h"
#include "../Utilities/SaveGameUtils.h"

using namespace std;

InputManager::InputManager(GameState* gs) {
    // Initialize key states
    keyStates = SDL_GetKeyboardState(nullptr);

    gameState = gs;

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

    if(IsKeyPressed(SDL_SCANCODE_S))
    {
        SaveGameUtils::SaveGame(*gameState);
    }
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
    if(button == SDL_BUTTON_LEFT)
    {
        HandleItemClick(gameState);

        for (const auto& clickablePair : clickables)
        {
            if (Intersection::IntersectionMouseRect(clickablePair.first->Rect, { mouseX, mouseY })) {
                // Handle the click based on the type of GameObject
                if (clickablePair.second == "cube_button")
                {
                    HandleCubeClick(gameState);
                    dynamic_cast<Image*>(clickablePair.first.get())->SetColor(MathUtils::GetRandomColor());
                    NotifyObserver("click_vfx");
                    
                    break;
                }
                if (clickablePair.second == "save_button")
                {
                    HandleSaveClick(gameState);
                    break; 
                }
            }
        }
    }
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

void InputManager::HandleItemClick(GameState* gameState) {
    Item* clickedItem = Intersection::GetClickedItem(GameObject::ActiveGameObjects, GetClickPos());
    if (clickedItem && clickedItem != nullptr) {
        if (gameState->CubeCount >= clickedItem->GetItemCost()) {
            gameState->CubeCount -= clickedItem->GetItemCost();
            clickedItem->BuyItem(1);
            gameState->UpdateItem(clickedItem);
        }
    }
}

void InputManager::HandleCubeClick(GameState* gameState)
{
    gameState->CubeCount++;
}

void InputManager::HandleSaveClick(GameState* gameState)
{
    SaveGameUtils::SaveGame(*gameState);
}

void InputManager::AddClickable(std::shared_ptr<GameObject> clickable, std::string name)
{
    clickables.emplace(clickable, name);
}

void InputManager::AddObserver(const std::string& id, std::shared_ptr<IClickObserver> observer)
{
    observers[id] = observer;
}

void InputManager::RemoveObserver(const std::string& id)
{
    observers.erase(id);
}

void InputManager::NotifyObserver(const std::string& id)
{
    auto it = observers.find(id);
    if (it != observers.end())
    {
        it->second->OnNotify();
    }
}

void InputManager::NotifyAll()
{
    for(auto observer : observers)
    {
        observer.second->OnNotify();
    }
}


