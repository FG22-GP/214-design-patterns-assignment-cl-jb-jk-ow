#pragma once
#include <queue>

#include "../Text/Text.h"

class TextPool
{
public:
    TextPool(Text* image, TextFactory* textFactory, int poolSize);
    
    int currentActiveObjects;
    
    GameObject* PoolGetObject();
    
    void PoolReturnObject(GameObject* gameObject);
    
    std::queue<GameObject*> ObjectPool;
};
