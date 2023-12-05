#pragma once
#include "Transform.h"

class Component {
public:
	Component(Transform initialLocalTransform);
	~Component();

	virtual void Awake() = 0;
	virtual void Enable() = 0;
	virtual void Disable() = 0;
	virtual void Update(float deltaTime) = 0;

	virtual void OnGameObjectTransformed(Transform newTransform);

	Transform transform;
};
