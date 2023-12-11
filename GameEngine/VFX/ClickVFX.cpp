#include "ClickVFX.h"

#include <SDL_mouse.h>

#include "../Input/InputManager.h"
#include "../Utilities/Consts.h"
#include "../Utilities/Intersection.h"
#include "../Utilities/TextPool.h"

class TextPool;


ClickVFX::ClickVFX(TextPool* poolToUpdate, int currentSpawnLimit)
{
    pool = poolToUpdate;
    limit = currentSpawnLimit;
}

void ClickVFX::Update() {

    for (GameObject* activePoolObj : ActivePoolObjects) {
        int xPos = activePoolObj->CurrentTransform.Position.X;
        int YPos = activePoolObj->CurrentTransform.Position.Y;
        if (YPos >= WINDOW_HEIGHT) {
            pool->PoolReturnObject(activePoolObj);
            ActivePoolObjects.erase(std::remove_if(ActivePoolObjects.begin(), ActivePoolObjects.end(),
                                [&activePoolObj](const GameObject* obj) {
                                    return obj == activePoolObj;
                                }),
                 ActivePoolObjects.end());
        }
        else {
            activePoolObj->SetPosition(Vector2(xPos, YPos - activePoolObj->poolObjSpeed));
        }
    }
}

void ClickVFX::OnClick()
{
    if (pool->currentActiveObjects < limit) {
        GameObject* Obj = pool->PoolGetObject();
        if (Obj != nullptr) {
            SDL_Point point;

            SDL_GetMouseState(&point.x, &point.y);
            
            Obj->Enable();
            Obj->SetPosition(Vector2(point.x - 10, point.y));
            ActivePoolObjects.push_back(Obj);
        }
    }
}
