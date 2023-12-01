#pragma once
#include <vector>
#include "GameObject.h"

class Pool {
public:
    Pool(int poolSize, GameObject* gameObject);
    std::vector<GameObject*> ObjectPool;
};
