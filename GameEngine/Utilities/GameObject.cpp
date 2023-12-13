#include "GameObject.h"

#include "MathUtils.h"
#include "../Utilities/Consts.h"

std::vector<std::shared_ptr<GameObject>> GameObject::ActiveGameObjects;

Transform::Transform()
{
	Position = Vector2(0, 0);
	Scale = Vector2(1, 1);
}

Transform::Transform(Vector2 position)
{
	Position = position;
	Scale = Vector2(1, 1);
}

Transform::Transform(Vector2 position, Vector2 scale) {
	Position = position;
	Scale = scale;
}

GameObject::GameObject(Transform transform) {
	// Create image rect
	
	Rect = new SDL_Rect{
		transform.Position.X,
		transform.Position.Y,
		transform.Scale.X,
		transform.Scale.Y
	};
	CurrentTransform = transform;

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

void GameObject::Update() {
}

void GameObject::SetPosition(Vector2 position) {
	CurrentTransform.Position = position;
	Rect->x = position.X;
	Rect->y = position.Y;
}

void GameObject::SetItemReference(::Item* item) {
	Item = item;
}
