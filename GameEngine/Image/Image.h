#pragma once

#include <SDL_render.h>
#include "../Utilities/GameObject.h"

class Image : public GameObject
{
private:
    SDL_Renderer* Renderer;

    const char* URL;
public:
    Image(Transform transform, const char* newImageURL, SDL_Renderer* renderer, SDL_Color color);
    
    void SetColor(SDL_Color Color);
    void SetTexture(const char* ImgUrl);

    const char* GetImageURL();

    SDL_Renderer* GetRenderer();
};
