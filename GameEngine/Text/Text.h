#pragma once

#include <SDL_ttf.h>

#include "TextFactory.h"
#include "../Utilities/GameObject.h"

class Text : public GameObject
{
public:
    Text(Vector2 position, TextFactory* textFactory, const char* fontURL, int fontSize, SDL_Color textColor, const char* text, SDL_Renderer* renderer);

    void SetColor(SDL_Color Color);
    void SetText(const char* NewText);
    void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    const char* GetTextURL();
    SDL_Renderer* GetRenderer();

    SDL_Color* backgroundColor;
    int fontSize;
    const char* text;
    TTF_Font* font;
    SDL_Surface* textSurface;
    SDL_Renderer* renderer;
    SDL_Color color;

protected:
    void RefreshText();

private:

    const char* URL;

    SDL_Renderer* Renderer;
};
