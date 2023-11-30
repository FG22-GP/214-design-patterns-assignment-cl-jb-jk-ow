#include "Image.h"
#include "..\Utilities/Consts.h"

#include <SDL_image.h>

Image::Image(int width, int height, const char* newImageURL, SDL_Renderer* renderer)
{
    imageWidth = width;
    imageHeight = height;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(newImageURL);
    
    //Convert surface to screen format
    imageTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    //Create image rect
    imageRect = new SDL_Rect{
    WINDOW_CENTER_X - (width / 2),
    WINDOW_CENTER_Y - (height / 2),
    imageWidth,
    imageHeight};
}

void Image::SetPosition(int x, int y)
{
    imageRect->x = x;
    imageRect->y = y;
}
