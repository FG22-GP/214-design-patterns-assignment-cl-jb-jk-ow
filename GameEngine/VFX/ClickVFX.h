#pragma once
#include <memory>
#include <vector>

#include "../Utilities/IClickObserver.h"

class TextPool;
class GameObject;

using namespace std;
class ClickVFX : public IClickObserver
{
public:

    void OnNotify() override;
    
    ClickVFX(shared_ptr<TextPool> poolToUpdate, int currentSpawnLimit);
    
    void Update();

    void OnClick();

    vector<GameObject*> ActivePoolObjects;

    SDL_Rect* GetRect() override;

private:
    TextPool* pool;
    int limit;
    
};
