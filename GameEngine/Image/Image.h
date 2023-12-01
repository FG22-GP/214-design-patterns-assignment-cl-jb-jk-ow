#pragma once

#include <SDL_render.h>

class Image
{
public:
    Image(int width, int height, const char* newImageURL, SDL_Renderer* renderer);

    void SetPosition(int x, int y);
    
    SDL_Texture* imageTexture;
    SDL_Rect* imageRect;

protected:
    int imageWidth, imageHeight;
};
