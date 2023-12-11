#pragma once
#include <queue>
#include "GameObject.h"

class Image;

class Pool {
public:
    Pool(Image* image, int poolSize);
    int currentActiveObjects;
    GameObject* PoolGetObject();
    void PoolReturnObject(GameObject* gameObject);
    std::queue<GameObject*> ObjectPool;
};
