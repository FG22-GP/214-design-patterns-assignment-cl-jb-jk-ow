#pragma once
#include <memory>
#include <vector>

#include "../Text/Text.h"
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

    vector<std::shared_ptr<Text>> ActivePoolObjects;

private:
    TextPool* pool;
    int limit;
    
};
