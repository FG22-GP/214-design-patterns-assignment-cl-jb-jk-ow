#include "Image.h"
#include "../Utilities/Consts.h"
#include <SDL_image.h>
#include "../Utilities/ImageURLs.h"

Image::Image(int width, int height, const char* newImageURL, SDL_Renderer* renderer)
{
    Renderer = renderer;
    imageWidth = width;
    imageHeight = height;

    SetTexture(newImageURL);

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

void Image::SetColor(SDL_Color Color) {
    SDL_SetTextureColorMod(imageTexture, Color.r, Color.g, Color.b);
}

void Image::SetTexture(const char* ImgUrl) {
    SDL_Surface* loadedSurface = IMG_Load(ImgUrl);
    imageTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}
