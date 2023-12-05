#include "Text.h"
#include <string>
#include "../Utilities/Consts.h"

Text::Text(Transform initialLocalTransform, const char* fontURL, int newFontSize, SDL_Color textColor, const char* newText, SDL_Renderer* renderer) : Renderer(initialLocalTransform) {
    // load font
    this->renderer = renderer;
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

/*
void Text::OnGameObjectTransformed(Transform newTransform) {
    Renderer::OnGameObjectTransformed(newTransform);

    RefreshText();
}
*/

void Text::RefreshText()
{
    // render the text into an unoptimized CPU surface
    textSurface = TTF_RenderText_Solid(font, text, color);
    
    // Create texture GPU-stored texture from surface pixels
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    
    // Get dimensions
    auto width = textSurface->w;
    auto height = textSurface->h;
    
    //Get rid of old loaded surface
    SDL_FreeSurface(textSurface);

    RefreshRect(Transform(Vector2(transform.position.x, transform.position.y), Vector2(width, height)));
}
