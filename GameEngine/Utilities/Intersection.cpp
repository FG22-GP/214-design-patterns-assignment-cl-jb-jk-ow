#include "Intersection.h"

#include <string>

bool Intersection::IntersectionMouseRect(SDL_Rect* Rect, std::vector<int> MousePos) {
    int mouseX = MousePos[0];
    int mouseY = MousePos[1];

    return (mouseX >= Rect->x && mouseX <= (Rect->x + Rect->w) &&
        mouseY >= Rect->y && mouseY <= (Rect->y + Rect->h));
}

GameObject* Intersection::GetClickedGameObject(std::vector<GameObject*>& gameobjects, std::vector<int> MousePos) {
    for (GameObject* gameobject : gameobjects) {
        if(IntersectionMouseRect(gameobject->Rect, MousePos)) {
            return gameobject;
        }
    }
    return nullptr;
}

Item* Intersection::GetClickedItem(std::vector<GameObject*>& gameobjects, std::vector<int> MousePos)
{
    for (GameObject* gameobject : gameobjects) {
        if(gameobject->Item != nullptr)
        {
            if(IntersectionMouseRect(gameobject->Rect, MousePos)) {
                return gameobject->Item;
            }
        }
    }
    return nullptr;
}
