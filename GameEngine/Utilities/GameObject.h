#pragma once
#include <memory>
#include <vector>
#include <SDL_render.h>
#include "Item.h"

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

class GameObject : std::enable_shared_from_this<GameObject>{
public:
    GameObject(Transform transform);
    
    ~GameObject();

    void Enable();
    void Disable();
    virtual void Update();

    void SetPosition(Vector2 position);
    void SetItemReference(::Item* item);

    static std::vector<GameObject*> ActiveGameObjects;
    Item* Item;
    SDL_Texture* Texture;
    SDL_Rect* Rect;
    Transform CurrentTransform;
    int poolObjSpeed;
};
