#pragma once

#include "Pool.h"

class CubeRain {
public:
    CubeRain();
    void Update(Pool* poolToUpdate, int currentSpawnLimit);
    std::vector<GameObject*> ActivePoolObjects;
};
