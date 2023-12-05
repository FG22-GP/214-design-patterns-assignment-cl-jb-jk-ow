#include "GameObject.h"
#include "../Utilities/Consts.h"

std::vector<GameObject*> GameObject::ActiveGameObjects;

GameObject::GameObject(Transform initialTransform) {
	transform = initialTransform;
	Enable();
}

GameObject::~GameObject() {
	Disable();
}

void GameObject::Enable() {
	ActiveGameObjects.push_back(this);
}

void GameObject::Disable() {
	std::erase_if(ActiveGameObjects, [this](GameObject* gameObject) {
		return gameObject == this;
		});
}

void GameObject::Update(float deltaTime) {
	for (Component* component : components)
	{
		component->Update(deltaTime);
	}
}

void GameObject::AddComponent(Component* component) {
	components.push_back(component);
	component->OnGameObjectTransformed(transform);
	
	auto* renderer = dynamic_cast<Renderer*>(component);
	if (renderer) {
		renderers.push_back(renderer);
	}
}

void GameObject::RemoveComponent(Component* component) {
	std::erase_if(components, [component](Component* iteratedComponent) {
		return component == iteratedComponent;
		});
}

void GameObject::SetPosition(Vector2 position) {
	transform.position = position;

	for (Component* component : components)
	{
		component->OnGameObjectTransformed(transform);
	}
}

std::vector<Component*> GameObject::GetComponents() {
	return components;
}

std::vector<Renderer*> GameObject::GetRenderers() {
	return renderers;
}
