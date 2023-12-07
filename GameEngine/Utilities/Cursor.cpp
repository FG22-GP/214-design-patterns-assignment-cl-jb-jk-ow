#include "Cursor.h"

#include <SDL_mouse.h>

Cursor::Cursor(SDL_Texture* cursorTexture)
{
    CursorTexture = cursorTexture;

    Rect.w = 20;
    Rect.h = 20;
    Point.w = 1;
    Point.h = 1;

    SDL_ShowCursor(false);
}

void Cursor::UpdateCursor()
{
    SDL_GetMouseState(&Point.x, &Point.y);
    Rect.x = Point.x - (Rect.w/2);
    Rect.y = Point.y - (Rect.h/2);
}

void Cursor::RenderCursor(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, CursorTexture, nullptr, &Rect);
}


