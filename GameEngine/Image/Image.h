#pragma once

#include <SDL_render.h>
#include "../Utilities/GameObject.h"

class Image : public GameObject
{
private:
    SDL_Renderer* Renderer;
public:
    Image(Transform transform, const char* newImageURL, SDL_Renderer* renderer);
    
    void SetColor(SDL_Color Color);
    void SetTexture(const char* ImgUrl);
};
