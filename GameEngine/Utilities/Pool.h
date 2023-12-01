#pragma once
#include <vector>
#include "GameObject.h"

class Pool {
public:
    Pool(int poolSize, GameObject* gameObject);
    GameObject* PoolGetObject();
    void PoolReleaseObject(GameObject* gameObject);
    std::vector<GameObject*> ObjectPool;
};
