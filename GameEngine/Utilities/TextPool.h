#pragma once
#include <queue>

#include "../Text/Text.h"

class TextPool
{
public:
    TextPool(std::shared_ptr<Text> text, std::shared_ptr<TextFactory> textFactory, int poolSize);
    
    int currentActiveObjects;
    
    std::shared_ptr<Text> PoolGetObject();
    
    void PoolReturnObject(std::shared_ptr<Text> gameObject);
    
    std::queue<std::shared_ptr<Text>> ObjectPool;
};
