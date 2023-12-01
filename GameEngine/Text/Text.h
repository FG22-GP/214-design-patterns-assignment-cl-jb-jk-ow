#pragma once

#include <SDL_ttf.h>

#include "../Utilities/GameObject.h"

class Text : public GameObject
{
public:
    Text(const char* fontURL, int fontSize, SDL_Color textColor, const char* text, SDL_Renderer* renderer);

    void SetPosition(int x, int y);

    void SetColor(SDL_Color Color);
    void SetText(const char* NewText);

    int fontSize;
    const char* text;
    TTF_Font* font;
    SDL_Texture* textTexture;
    SDL_Surface* textSurface;
    SDL_Rect* textRect;
    SDL_Renderer* renderer;
    SDL_Color color;

protected:
    void RefreshText();
};
