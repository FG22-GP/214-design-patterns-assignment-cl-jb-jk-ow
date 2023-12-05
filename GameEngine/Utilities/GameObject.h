#pragma once
#include <vector>
#include "../Transform.h"
#include "../Renderer.h"

class Component;

class GameObject {
public:
    GameObject(Transform initialTransform);
    ~GameObject();

    virtual void Enable();
    virtual void Disable();
    virtual void Update(float deltaTime);

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    void SetPosition(Vector2 position);

    std::vector<Component*> GetComponents();
    std::vector<Renderer*> GetRenderers();
    
    static std::vector<GameObject*> ActiveGameObjects;

    Transform transform;

protected:
    std::vector<Component*> components;

private:
    std::vector<Renderer*> renderers;
};
