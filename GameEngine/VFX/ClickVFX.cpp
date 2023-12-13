#include "ClickVFX.h"

#include <SDL_mouse.h>

#include "../Input/InputManager.h"
#include "../Utilities/GameObjectFactory.h"
#include "../Utilities/Intersection.h"
#include "../Utilities/TextPool.h"

class TextPool;


void ClickVFX::OnNotify()
{
  OnClick();  
}

ClickVFX::ClickVFX(std::shared_ptr<TextPool> poolToUpdate, int currentSpawnLimit)
{
    pool = poolToUpdate.get();
    limit = currentSpawnLimit;
}

void ClickVFX::Update() {

    for (std::shared_ptr<Text> activePoolObj : ActivePoolObjects) {
        int xPos = activePoolObj->CurrentTransform.Position.X;
        int YPos = activePoolObj->CurrentTransform.Position.Y;
        if (YPos <= 0) {
            pool->PoolReturnObject(activePoolObj);
            ActivePoolObjects.erase(std::remove_if(ActivePoolObjects.begin(), ActivePoolObjects.end(),
                                [&activePoolObj](const std::shared_ptr<Text> obj) {
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
        std::shared_ptr<Text> Obj = pool->PoolGetObject();
        if (Obj != nullptr) {
            SDL_Point point;

            SDL_GetMouseState(&point.x, &point.y);
            
            GameObjectFactory::Enable(Obj);
            Obj->SetPosition(Vector2(point.x - 10, point.y));
            ActivePoolObjects.push_back(Obj);
        }
    }
}
