#pragma once
#include <vector>

#include "../Utilities/IClickObserver.h"

class TextPool;
class GameObject;

using namespace std;
class ClickVFX : public IClickObserver
{
public:

    void OnNotify() override;
    
    ClickVFX(TextPool* poolToUpdate, int currentSpawnLimit);
    
    void Update();

    void OnClick();

    vector<GameObject*> ActivePoolObjects;

private:
    TextPool* pool;
    int limit;
    
};
