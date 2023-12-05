#include "GameObject.h"

GameObject::GameObject(Transform transform)
{
	GameObjects.push_back(this);
	CurrentTransform = transform;
}