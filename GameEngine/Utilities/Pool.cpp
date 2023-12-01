#include "Pool.h"

Pool::Pool(int poolSize, GameObject* gameObject) {
    for(int i = 0; i < poolSize; i++) {
        gameObject = new GameObject;
        ObjectPool.push_back(gameObject);
    }
}
