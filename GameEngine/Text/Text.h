#pragma once

#include <SDL_ttf.h>

#include "../Utilities/GameObject.h"

class Text : public GameObject
{
public:
    Text(Vector2 position, const char* fontURL, int fontSize, SDL_Color textColor, const char* text, SDL_Renderer* renderer);

    void SetColor(SDL_Color Color);
    void SetText(const char* NewText);

    int fontSize;
    const char* text;
    TTF_Font* font;
    SDL_Surface* textSurface;
    SDL_Renderer* renderer;
    SDL_Color color;

protected:
    void RefreshText();
};
