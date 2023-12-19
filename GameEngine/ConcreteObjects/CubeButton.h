#pragma once
#include "../Image/Image.h"
#include <SDL_render.h>
#include "../Utilities/GameObject.h"
#include "../Utilities/IClickObserver.h"

class CubeButton : public Image, public IClickObserver
{
public:

    CubeButton(Transform transform, const char* newImageURL, SDL_Renderer* renderer, SDL_Color color);

    void OnNotify() override;

    SDL_Rect* GetRect() override;

};
