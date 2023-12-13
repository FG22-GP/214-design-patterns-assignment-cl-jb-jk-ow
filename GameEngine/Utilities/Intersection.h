#pragma once
#include <memory>
#include <SDL_rect.h>
#include <vector>
#include "GameObject.h"

class Intersection {
public:
    static bool IntersectionMouseRect(SDL_Rect* Rect, std::vector<int> MousePos);
    static std::shared_ptr<GameObject> GetClickedGameObject(std::vector<std::shared_ptr<GameObject>>& gameobjects, std::vector<int> MousePos);
    static Item* GetClickedItem(std::vector<std::shared_ptr<GameObject>>& gameobjects, std::vector<int> MousePos);
};
