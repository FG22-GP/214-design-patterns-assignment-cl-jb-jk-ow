#include "CubeButton.h"

#include "../Utilities/GameState.h"


CubeButton::CubeButton(Transform transform, const char* newImageURL, SDL_Renderer* renderer, SDL_Color color)
: Image(transform, newImageURL, renderer, color)
{
}

void CubeButton::OnNotify()
{
    GameState::AddToCubeCount(1);
}

SDL_Rect* CubeButton::GetRect()
{
    return Rect;
}
