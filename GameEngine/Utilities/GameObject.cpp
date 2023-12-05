#include "GameObject.h"

std::vector<GameObject*> GameObject::ActiveGameObjects;

GameObject::GameObject(Transform transform) {
	CurrentTransform = transform;
	Enable();
}

GameObject::~GameObject() {
	Disable();
}

void GameObject::Enable() {
	ActiveGameObjects.push_back(this);
}

void GameObject::Disable(){
	std::erase_if(ActiveGameObjects, [this](GameObject* gameObject) {
		return gameObject == this;
		});
}

/*
void GameObject::Update() {
	for (GameObject* gameObject : GameObjects)
	{
		gameObject.
	}
}
*/