#include "GameObject.h"

#include "MathUtils.h"


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
