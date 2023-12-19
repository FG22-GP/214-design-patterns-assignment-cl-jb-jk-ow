#include "SaveButton.h"

#include "../Utilities/GameState.h"
#include "../Utilities/SaveGameUtils.h"


SaveButton::SaveButton(Vector2 position, std::shared_ptr<TextFactory> textFactory, const char* fontURL, int fontSize, SDL_Color textColor, const char* text, SDL_Renderer* renderer)
    :Text(position, textFactory, fontURL, fontSize, textColor, text, renderer)
{
}

void SaveButton::OnNotify()
{
    SaveGameUtils::SaveGame(*GameState::Instance);
}

SDL_Rect* SaveButton::GetRect()
{
    return Rect;
}
