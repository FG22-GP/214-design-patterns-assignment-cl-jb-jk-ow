#include "Text.h"
#include "../Utilities/Consts.h"

Text::Text(const char* fontURL, int newFontSize, SDL_Color textColor, const char* newText, SDL_Renderer* newRenderer):
    GameObject(this->CurrentTransform) {
    // load font
    renderer = newRenderer;
    color = textColor;
    text = newText;
    fontSize = newFontSize;
    font = TTF_OpenFont(fontURL, newFontSize);

    RefreshText();
}

void Text::SetPosition(int x, int y)
{
    textRect->x = x;
    textRect->y = y;
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
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    
    // Get image dimensions
    auto width = textSurface->w;
    auto height = textSurface->h;
    
    //Get rid of old loaded surface
    SDL_FreeSurface(textSurface);

    //Create image rect
    textRect = new SDL_Rect{
        WINDOW_CENTER_X - (width / 2),
        WINDOW_CENTER_Y - (height / 2),
        width,
        height};
}
