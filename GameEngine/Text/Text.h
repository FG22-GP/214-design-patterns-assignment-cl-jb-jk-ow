#pragma once

#include <SDL_ttf.h>

class Text
{
public:
    Text(const char* fontURL, int fontSize, SDL_Color textColor, const char* text, SDL_Renderer* renderer);

    void SetPosition(int x, int y);
    
    TTF_Font* font;
    SDL_Texture* textTexture;
    SDL_Surface* textSurface;
    SDL_Rect* textRect;
};
