#pragma once
#include <SDL_render.h>
#include "Component.h"

class Renderer : public Component {
public:
	Renderer(Transform initialLocalTransform);
	~Renderer();

	virtual void Awake();
	virtual void Enable();
	virtual void Disable();
	virtual void Update(float deltaTime);
	virtual void OnGameObjectTransformed(Transform newTransform);

	SDL_Texture* texture;
	SDL_Rect* rect;

protected:
	void RefreshRect(Transform newTransform);

	SDL_Renderer* renderer;
};
