#pragma once
#include <SDL_rect.h>

class IClickObserver
{
public:
    virtual void OnNotify() = 0;

    virtual SDL_Rect* GetRect() = 0;
    
};
