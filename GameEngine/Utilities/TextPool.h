#pragma once
#include <queue>

#include "../Text/Text.h"

class TextPool
{
public:
    TextPool(std::shared_ptr<Text> text, std::shared_ptr<TextFactory> textFactory, int poolSize);
    
    int currentActiveObjects;
    
    GameObject* PoolGetObject();
    
    void PoolReturnObject(GameObject* gameObject);
    
    std::queue<GameObject*> ObjectPool;
};
