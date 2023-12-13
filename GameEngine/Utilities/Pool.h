#pragma once
#include <memory>
#include <queue>
#include "GameObject.h"

class Image;

class Pool {
public:
    Pool(std::shared_ptr<Image> image, int poolSize);
    int currentActiveObjects;
    GameObject* PoolGetObject();
    void PoolReturnObject(GameObject* gameObject);
    std::queue<GameObject*> ObjectPool;
};
