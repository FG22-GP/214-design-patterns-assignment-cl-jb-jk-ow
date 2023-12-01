#pragma once
#include <SDL_render.h>

class GameObject {
public:
    virtual void SetColor(SDL_Color Color);
    virtual void SetTexture(const char* ImgUrl);
    
};
