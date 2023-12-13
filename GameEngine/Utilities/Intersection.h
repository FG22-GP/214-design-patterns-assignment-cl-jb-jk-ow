#pragma once
#include <SDL_rect.h>
#include <vector>
#include "GameObject.h"

class Intersection {
public:
    static bool IntersectionMouseRect(SDL_Rect* Rect, std::vector<int> MousePos);
    static GameObject* GetClickedGameObject(std::vector<GameObject*>& gameobjects, std::vector<int> MousePos);
    static Item* GetClickedItem(std::vector<GameObject*>& gameobjects, std::vector<int> MousePos);
};
