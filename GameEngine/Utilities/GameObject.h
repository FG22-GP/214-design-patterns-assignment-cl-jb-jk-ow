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
    static std::vector<GameObject*> GameObjects;
    Transform CurrentTransform;
};
