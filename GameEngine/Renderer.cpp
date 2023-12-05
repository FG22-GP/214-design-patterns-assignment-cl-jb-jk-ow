#include "Renderer.h"

Renderer::Renderer(Transform initialLocalTransform) : Component(initialLocalTransform) { }

Renderer::~Renderer() { }

void Renderer::Awake() {
}

void Renderer::Enable() {
}

void Renderer::Disable() {
}

void Renderer::Update(float deltaTime) {
}

void Renderer::OnGameObjectTransformed(Transform newTransform) {
    Component::OnGameObjectTransformed(newTransform);

    RefreshRect(transform);
}

void Renderer::RefreshRect(Transform newTransform) {
    rect = new SDL_Rect{
        transform.position.x,
        transform.position.y,
        transform.scale.x,
        transform.scale.y
    };
}
