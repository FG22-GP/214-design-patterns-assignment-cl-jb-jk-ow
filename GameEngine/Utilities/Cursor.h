#pragma once
#include <memory>
#include <SDL_render.h>

class Cursor
{
public:
    SDL_Texture* CursorTexture;
    SDL_Rect Rect;
    SDL_Rect Point;

    Cursor(std::shared_ptr<SDL_Texture> cursorTexture);

    void UpdateCursor();
    void RenderCursor(SDL_Renderer* renderer);
};
