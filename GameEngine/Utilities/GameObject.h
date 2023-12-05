#pragma once
#include <vector>
#include <SDL_render.h>

struct Vector2 {
public:
    int X;
    int Y;
};

struct Transform {
public:
    Transform();
    Transform(Vector2 position);
    Transform(Vector2 position, Vector2 scale);
    Vector2 Position;
    Vector2 Scale;
};

class GameObject {
public:
    GameObject(Transform transform);
    ~GameObject();

    void Enable();
    void Disable();

    void SetPosition(Vector2 position);

    static std::vector<GameObject*> ActiveGameObjects;
    SDL_Texture* Texture;
    SDL_Rect* Rect;
    Transform CurrentTransform;
};
