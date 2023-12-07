#pragma once
#include <queue>
#include "GameObject.h"

class Pool {
public:
    Pool(int poolSize, SDL_Renderer* Renderer);
    int currentActiveObjects;
    GameObject* PoolGetObject();
    void PoolReturnObject(GameObject* gameObject);
    std::queue<GameObject*> ObjectPool;
};
