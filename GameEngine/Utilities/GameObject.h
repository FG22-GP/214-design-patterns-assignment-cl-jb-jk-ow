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
    ~GameObject();

    void Enable();
    void Disable();
    //static void Update();

    static std::vector<GameObject*> ActiveGameObjects;
    Transform CurrentTransform;
};
