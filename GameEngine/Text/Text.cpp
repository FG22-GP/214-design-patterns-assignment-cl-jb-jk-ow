#include "Text.h"
#include "..\Utilities/Consts.h"

Text::Text(const char* fontURL, int fontSize, SDL_Color textColor, const char* text, SDL_Renderer* renderer)
{
    // load font
    auto font = TTF_OpenFont(fontURL, fontSize);

    // render the text into an unoptimized CPU surface
    textSurface = TTF_RenderText_Solid(font, text, textColor);
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

void Text::SetPosition(int x, int y)
{
    textRect->x = x;
    textRect->y = y;
}
