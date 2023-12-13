#include "Pool.h"

#include "Consts.h"
#include "ImageURLs.h"
#include "MathUtils.h"
#include "../Image/Image.h"

Pool::Pool(std::shared_ptr<Image> image, int poolSize) {
    for (int i = 0; i < poolSize; i++) {
        auto img = std::make_shared<Image>(image->CurrentTransform, image->GetImageURL(), image->GetRenderer(), MathUtils::GetRandomColor());
        ObjectPool.push(img);
        img->Disable();
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
    gameObject->Disable();
    ObjectPool.push(gameObject);
    currentActiveObjects -= 1;
}
