#include "Pool.h"

Pool::Pool(int poolSize, GameObject* gameObject) {
    for (int i = 0; i < poolSize; i++) {
        gameObject = new GameObject;
        ObjectPool.push(gameObject);
    }
}

GameObject* Pool::PoolGetObject() {
    if (!ObjectPool.empty()) {
        GameObject* FrontObj = ObjectPool.front();
        ObjectPool.pop();
        return FrontObj;
    }
}

void Pool::PoolReleaseObject(GameObject* gameObject) {
    ObjectPool.push(gameObject);
}
