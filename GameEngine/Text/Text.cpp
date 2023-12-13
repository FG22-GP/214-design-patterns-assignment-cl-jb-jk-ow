#include "Text.h"

#include <memory>
#include <string>

Text::Text(Vector2 position, std::shared_ptr<TextFactory> textFactory, const char* fontURL, int newFontSize, SDL_Color textColor, const char* newText, SDL_Renderer* newRenderer) : GameObject(Transform(position)) {
    // load font
    backgroundColor = new SDL_Color{0, 0, 0, 0};
    renderer = newRenderer;
    color = textColor;
    color.a = 255;
    text = newText;
    fontSize = newFontSize;
    font = textFactory->GetFont(fontURL, fontSize);
    URL = fontURL;
    Renderer = newRenderer;

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

void Text::SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_Color* NewColor = new SDL_Color{r, g, b, a};
    backgroundColor = NewColor;
    RefreshText();
}

void Text::RefreshText()
{

    SDL_Surface* textBGSurface = nullptr;
    
    //if a background color is set, setup bg
    if(backgroundColor->a > 0) {
        textBGSurface = SDL_CreateRGBSurface(0, Rect->w, Rect->h, 32, 0, 0, 0, 0);
        Uint32 backgroundColorValue = SDL_MapRGBA(textBGSurface->format, backgroundColor->r, backgroundColor->g, backgroundColor->b, backgroundColor->a);
        SDL_FillRect(textBGSurface, nullptr, backgroundColorValue);
    }
    // render the text into an unoptimized CPU surface
    textSurface = TTF_RenderText_Solid(font, text, color);

    //if a background color is set, continue setting up bg
    if(textBGSurface != nullptr) {
        SDL_BlitSurface(textSurface, nullptr, textBGSurface, nullptr);
        SDL_FreeSurface(textSurface);
        textSurface = textBGSurface;
    }
    
    // Create texture GPU-stored texture from surface pixels
    Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    
    // Get dimensions
    auto width = textSurface->w;
    auto height = textSurface->h;
    
    //Get rid of old loaded surface
    if (textBGSurface != nullptr) {
        SDL_FreeSurface(textBGSurface);
    }
    else {
        SDL_FreeSurface(textSurface);
    }

    //Create rect
    Rect = new SDL_Rect{
        CurrentTransform.Position.X,
        CurrentTransform.Position.Y,
        width,
        height 
    };
}

const char* Text::GetTextURL()
{
    return URL;
}

SDL_Renderer* Text::GetRenderer()
{
    return Renderer;
}
