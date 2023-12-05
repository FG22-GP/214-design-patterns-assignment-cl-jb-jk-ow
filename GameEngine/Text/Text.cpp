#include "Text.h"
#include "../Utilities/Consts.h"

Text::Text(Vector2 position, const char* fontURL, int newFontSize, SDL_Color textColor, const char* newText, SDL_Renderer* newRenderer) : GameObject(Transform(position)) {
    // load font
    renderer = newRenderer;
    color = textColor;
    text = newText;
    fontSize = newFontSize;
    font = TTF_OpenFont(fontURL, newFontSize);

    RefreshText();
}

void Text::SetColor(SDL_Color Color)
{
    color = Color;
    RefreshText();
}

void Text::SetText(const char* NewText)
{
    text = NewText;
    RefreshText();
}

void Text::RefreshText()
{
    // render the text into an unoptimized CPU surface
    textSurface = TTF_RenderText_Solid(font, text, color);
    int textWidth, textHeight;
    
    // Create texture GPU-stored texture from surface pixels
    Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    
    // Get dimensions
    auto width = textSurface->w;
    auto height = textSurface->h;
    
    //Get rid of old loaded surface
    SDL_FreeSurface(textSurface);

    //Create rect
    Rect = new SDL_Rect{
        CurrentTransform.Position.X,
        CurrentTransform.Position.Y,
        width,
        height 
    };
}
