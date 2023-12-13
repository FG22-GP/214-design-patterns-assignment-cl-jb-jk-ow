#include "Pool.h"

#include "MathUtils.h"
#include "../Image/Image.h"

Pool::Pool(std::shared_ptr<Image> image, int poolSize, std::shared_ptr<GameObjectFactory> goFactory){
    for (int i = 0; i < poolSize; i++) {
        std::shared_ptr<Image> img = goFactory->ConstructGameObject(new Image(image->CurrentTransform, image->GetImageURL(), image->GetRenderer(), MathUtils::GetRandomColor()));
        ObjectPool.push(img);
        GameObjectFactory::Disable(img);
    }
    currentActiveObjects = 0;
}

std::shared_ptr<GameObject> Pool::PoolGetObject() {
    if (ObjectPool.empty()) return nullptr;
    std::shared_ptr<GameObject> FrontObj = ObjectPool.front();
    ObjectPool.pop();
    currentActiveObjects += 1;
    FrontObj->poolObjSpeed = MathUtils::GetRandomInt(1, 3);
    return FrontObj;
}

void Pool::PoolReturnObject(std::shared_ptr<GameObject> gameObject) {
    GameObjectFactory::Disable(gameObject);
    ObjectPool.push(gameObject);
    currentActiveObjects -= 1;
}
