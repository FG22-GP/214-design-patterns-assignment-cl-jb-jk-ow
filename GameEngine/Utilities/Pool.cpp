#include "Pool.h"

Pool::Pool(int poolSize, GameObject* gameObject) {
    for (int i = 0; i < poolSize; i++) {
        GameObject* newGameObject = new GameObject(*gameObject);
        ObjectPool.push(newGameObject);
    }
}

GameObject* Pool::PoolGetObject() {
    if (ObjectPool.empty()) return nullptr;

    GameObject* FrontObj = ObjectPool.front();
    ObjectPool.pop();
    return FrontObj;
}

void Pool::PoolReleaseObject(GameObject* gameObject) {
    ObjectPool.push(gameObject);
}
