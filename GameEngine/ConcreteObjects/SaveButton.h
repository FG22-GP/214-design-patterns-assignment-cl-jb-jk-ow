#pragma once
#include <SDL_render.h>

#include "../Text/Text.h"
#include "../Utilities/IClickObserver.h"
#include "../Utilities/GameObject.h"

class SaveButton : public Text, public IClickObserver
{
public:

    SaveButton(Vector2 position, std::shared_ptr<TextFactory> textFactory, const char* fontURL, int fontSize, SDL_Color textColor, const char* text, SDL_Renderer* renderer);

    void OnNotify() override;

    SDL_Rect* GetRect() override;
    
};
