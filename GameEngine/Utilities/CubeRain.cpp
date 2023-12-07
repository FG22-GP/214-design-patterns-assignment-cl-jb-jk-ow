#include "CubeRain.h"
#include "Consts.h"
#include "MathUtils.h"


CubeRain::CubeRain() {
}

void CubeRain::Update(Pool* poolToUpdate, int currentSpawnLimit) {
    //printf("current active: %d\n", poolToUpdate->currentActiveObjects);
    if (poolToUpdate->currentActiveObjects < currentSpawnLimit) {
        GameObject* Obj = poolToUpdate->PoolGetObject();
        if (Obj != nullptr) {
            int RandomXPos = MathUtils::GetRandomInt(630, WINDOW_WIDTH - 300);
            int RandomYPos = MathUtils::GetRandomInt(20, 800);
            Obj->Enable();
            Obj->SetPosition(Vector2(RandomXPos, RandomYPos * -1)); //todo: window height, 200 is for testing
            ActivePoolObjects.push_back(Obj);
        }
    }

    for (GameObject* activePoolObj : ActivePoolObjects) {
        int xPos = activePoolObj->CurrentTransform.Position.X;
        int YPos = activePoolObj->CurrentTransform.Position.Y;
        if (YPos >= WINDOW_HEIGHT) {
            poolToUpdate->PoolReturnObject(activePoolObj);
            ActivePoolObjects.erase(std::remove_if(ActivePoolObjects.begin(), ActivePoolObjects.end(),
                                [&activePoolObj](const GameObject* obj) {
                                    return obj == activePoolObj;
                                }),
                 ActivePoolObjects.end());
        }
        else {
            activePoolObj->SetPosition(Vector2(xPos, YPos + activePoolObj->poolObjSpeed));
        }
    }
}
