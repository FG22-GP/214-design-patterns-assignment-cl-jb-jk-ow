#pragma once
#include <SDL_render.h>

class Cursor
{
public:
    SDL_Texture* CursorTexture;
    SDL_Rect Rect;
    SDL_Rect Point;

    Cursor(SDL_Texture* cursorTexture);

    void UpdateCursor();
    void RenderCursor(SDL_Renderer* renderer);
};
