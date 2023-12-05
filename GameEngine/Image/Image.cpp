#include "Image.h"
#include <SDL_image.h>

Image::Image(Transform initialLocalTransform, const char* newImageURL, SDL_Renderer* renderer) : Renderer(initialLocalTransform) {
    this->renderer = renderer;
    SetTexture(newImageURL);
}

void Image::SetColor(SDL_Color Color) {
    SDL_SetTextureColorMod(texture, Color.r, Color.g, Color.b);
}

void Image::SetTexture(const char* ImgUrl) {
    SDL_Surface* loadedSurface = IMG_Load(ImgUrl);
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}
