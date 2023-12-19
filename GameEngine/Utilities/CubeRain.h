#pragma once

#include "Pool.h"

class CubeRain {
public:
    CubeRain();
    void Update(std::shared_ptr<Pool> poolToUpdate, int currentSpawnLimit);
    std::vector<std::shared_ptr<GameObject>> ActivePoolObjects;
};
