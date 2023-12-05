#pragma once
#include <SDL_render.h>
#include "../Renderer.h"

class Image : public Renderer {
public:
    Image(Transform initialLocalTransform, const char* newImageURL, SDL_Renderer* renderer);
    
    void SetColor(SDL_Color Color);
    void SetTexture(const char* ImgUrl);
};
