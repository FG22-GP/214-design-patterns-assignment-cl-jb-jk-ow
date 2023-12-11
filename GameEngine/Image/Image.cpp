#include "Image.h"
#include <SDL_image.h>

Image::Image(Transform transform, const char* newImageURL, SDL_Renderer* renderer, SDL_Color color) : GameObject(transform) {
    Renderer = renderer;
    SetTexture(newImageURL);
    SetColor(color);
    URL = newImageURL;
}

void Image::SetColor(SDL_Color Color) {
    SDL_SetTextureColorMod(Texture, Color.r, Color.g, Color.b);
}

void Image::SetTexture(const char* ImgUrl) {
    SDL_Surface* loadedSurface = IMG_Load(ImgUrl);
    Texture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}

const char* Image::GetImageURL()
{
    return URL;
}

SDL_Renderer* Image::GetRenderer()
{
    return Renderer;
}
