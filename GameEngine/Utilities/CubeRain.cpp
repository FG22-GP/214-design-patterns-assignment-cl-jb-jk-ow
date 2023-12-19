#include "CubeRain.h"
#include "Consts.h"
#include "MathUtils.h"

std::vector<std::shared_ptr<GameObject>> objectsToRemove;

CubeRain::CubeRain() {
}



void CubeRain::Update(std::shared_ptr<Pool> poolToUpdate, int currentSpawnLimit) {
    //printf("current active: %d\n", poolToUpdate->currentActiveObjects);
    if (poolToUpdate->currentActiveObjects < currentSpawnLimit) {
        std::shared_ptr<GameObject> Obj = poolToUpdate->PoolGetObject();
        if (Obj != nullptr) {
            int RandomXPos = MathUtils::GetRandomInt(630, WINDOW_WIDTH - 300);
            int RandomYPos = MathUtils::GetRandomInt(20, 800);
            Obj->Enable();
            Obj->SetPosition(Vector2(RandomXPos, RandomYPos * -1)); //todo: window height, 200 is for testing
            ActivePoolObjects.push_back(Obj);
        }
    }
    
    for (auto& activePoolObj : ActivePoolObjects) {
        int xPos = activePoolObj->CurrentTransform.Position.X;
        int yPos = activePoolObj->CurrentTransform.Position.Y;

        if (yPos >= WINDOW_HEIGHT) {
            poolToUpdate->PoolReturnObject(activePoolObj);
            objectsToRemove.push_back(activePoolObj);
        } else {
            activePoolObj->SetPosition(Vector2(xPos, yPos + activePoolObj->poolObjSpeed));
        }
    }

    for (const auto& objToRemove : objectsToRemove) {
        ActivePoolObjects.erase(std::remove(ActivePoolObjects.begin(), ActivePoolObjects.end(), objToRemove),
                                ActivePoolObjects.end());
    }
    objectsToRemove.clear();
}
