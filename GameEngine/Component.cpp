#include "Component.h"

Component::Component(Transform initialLocalTransform) {
	// TODO: Use linear algreba for the transforms instead of just a position offset
	transform.position.x += initialLocalTransform.position.x;
	transform.position.y += initialLocalTransform.position.y;
}

Component::~Component() {
}


void Component::OnGameObjectTransformed(Transform newTransform) {
	transform = newTransform; 
}
