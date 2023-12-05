#include "GameObject.h"

GameObject::GameObject(Transform transform){
	CurrentTransform = transform;
}

void GameObject::Enable(){
	ActiveGameObjects.push_back(this);
}

void GameObject::Disable(){
	std::erase_if(ActiveGameObjects, [this](GameObject* gameObject) {
		return gameObject == this;
		});
}

/*
void GameObject::Update(){
	for (GameObject* gameObject : GameObjects)
	{
		gameObject.
	}
}
*/