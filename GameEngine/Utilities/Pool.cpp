#include "Pool.h"

#include "Consts.h"
#include "ImageURLs.h"
#include "MathUtils.h"
#include "../Image/Image.h"

Pool::Pool(int poolSize, SDL_Renderer* Renderer) {
    for (int i = 0; i < poolSize; i++) {
        Image* img = new Image(Transform(Vector2(0, WINDOW_CENTER_Y - 0), Vector2(20, 20)), IMG_CUBE_URL, Renderer, MathUtils::GetRandomColor());
        ObjectPool.push(img);
        img->Disable();
    }
        currentActiveObjects = 0;
}

GameObject* Pool::PoolGetObject() {
    if (ObjectPool.empty()) return nullptr;
    GameObject* FrontObj = ObjectPool.front();
    ObjectPool.pop();
    currentActiveObjects += 1;
    FrontObj->poolObjSpeed = MathUtils::GetRandomInt(1, 3);
    return FrontObj;
}

void Pool::PoolReturnObject(GameObject* gameObject) {
    gameObject->Disable();
    ObjectPool.push(gameObject);
    currentActiveObjects -= 1;
}
