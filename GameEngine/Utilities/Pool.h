#pragma once
#include <queue>
#include "GameObject.h"

class Pool {
public:
    Pool(int poolSize, GameObject* gameObject);
    GameObject* PoolGetObject();
    void PoolReleaseObject(GameObject* gameObject);
    std::queue<GameObject*> ObjectPool;
};
