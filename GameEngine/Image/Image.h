#pragma once

#include <SDL_render.h>

#include "../Utilities/GameObject.h"

class Image : public GameObject
{
private:
    SDL_Renderer* Renderer;
public:
    Image(int width, int height, const char* newImageURL, SDL_Renderer* renderer);
    
    void SetPosition(int x, int y);
    
    SDL_Texture* imageTexture;
    SDL_Rect* imageRect;

    void SetColor(SDL_Color Color);
    void SetTexture(const char* ImgUrl);
    

protected:
    int imageWidth, imageHeight;
};
