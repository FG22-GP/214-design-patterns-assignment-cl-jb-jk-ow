#pragma once
#include <vector>

struct Position {
public:
    int X;
    int Y;
};

struct Transform {
public:
    Position Position;
};

class GameObject {
public:
    GameObject(Transform transform);

    void Enable();
    void Disable();
    //static void Update();

    std::vector<GameObject*> ActiveGameObjects; // TODO: Should be static
    Transform CurrentTransform;
};
