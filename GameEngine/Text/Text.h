#pragma once
#include <SDL_ttf.h>
#include "../Renderer.h"

class Text : public Renderer
{
public:
    Text(Transform initialLocalTransform, const char* fontURL, int fontSize, SDL_Color textColor, const char* text, SDL_Renderer* renderer);

    //virtual void OnGameObjectTransformed(Transform newTransform);

    void SetColor(SDL_Color Color);
    void SetText(const char* NewText);

    int fontSize;
    const char* text;
    TTF_Font* font;
    SDL_Surface* textSurface;
    SDL_Color color;

protected:
    void RefreshText();
};
