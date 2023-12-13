#include "InputManager.h"

#include "../Image/Image.h"
#include "../Text/Text.h"
#include "../Utilities/GameObject.h"
#include "../Utilities/Intersection.h"
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

        for (const auto& [first, second] : observers)
        {
            if (Intersection::IntersectionMouseRect(second->GetRect(), { mouseX, mouseY })) {
                // Handle the click based on the type of GameObject
                if (first == "cube_button")
                {
                    dynamic_cast<Image*>(second.get())->SetColor(MathUtils::GetRandomColor());
                    NotifyObserver("click_vfx");
                    NotifyObserver("cube_button");
                    
                    break;
                }
                if (first == "save_button")
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
        if (GameState::CubeCount >= clickedItem->GetItemCost()) {
            GameState::CubeCount -= clickedItem->GetItemCost();
            clickedItem->BuyItem(1);
            gameState->UpdateItem(clickedItem);
        }
    }
}

void InputManager::HandleCubeClick(GameState* gameState)
{
    GameState::AddToCubeCount(1);
}

void InputManager::HandleSaveClick(GameState* gameState)
{
    SaveGameUtils::SaveGame(*gameState);
}

void InputManager::AddClickable(std::shared_ptr<GameObject> clickable, const std::string& name)
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
    const auto it = observers.find(id);
    if (it != observers.end())
    {
        it->second->OnNotify();
    }
}

void InputManager::NotifyAll()
{
    for(const auto observer : observers)
    {
        observer.second->OnNotify();
    }
}


