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

    Item* Item;
    void Enable();
    void Disable();
    virtual void Update();

    void SetPosition(Vector2 position);
    
    static std::vector<std::shared_ptr<GameObject>> ActiveGameObjects;
    SDL_Texture* Texture;
    SDL_Rect* Rect;
    Transform CurrentTransform;
    int poolObjSpeed;

    void SetItemReference(::Item* item);
};
