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
        std::vector<Renderer*> renderers = gameobject->GetRenderers();
        for (Renderer* renderer : renderers) {
            if (IntersectionMouseRect(renderer->rect, MousePos)) {
                return gameobject;
            }
        }
    }
    return nullptr;
}

Item* Intersection::GetClickedItem(std::vector<GameObject*>& gameobjects, std::vector<int> MousePos)
{
    for (GameObject* gameobject : gameobjects) {
        auto* item = dynamic_cast<Item*>(gameobject);
        if (item) {
            std::vector<Renderer*> renderers = item->GetRenderers();
            for (Renderer* renderer : renderers) {
                if (IntersectionMouseRect(renderer->rect, MousePos)) {
                    return item;
                }
            }
        }
    }
    return nullptr;
}
