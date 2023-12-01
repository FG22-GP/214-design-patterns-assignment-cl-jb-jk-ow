#include "Pool.h"

Pool::Pool(int poolSize, GameObject* gameObject) {
    for(int i = 0; i < poolSize; i++) {
        gameObject = new GameObject;
        ObjectPool.push_back(gameObject);
    }
}

GameObject* Pool::PoolGetObject() {
    for (auto GameObject : ObjectPool) {
        if(GameObject->isActive) continue;
        return GameObject;
    }
    printf("No objects left in pool :(");
    return nullptr;
}

void Pool::PoolReleaseObject(GameObject* gameObject) {
    
}
