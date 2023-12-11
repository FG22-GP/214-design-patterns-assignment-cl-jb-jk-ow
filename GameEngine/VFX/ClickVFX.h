#pragma once
#include <vector>

class TextPool;
class GameObject;

using namespace std;
class ClickVFX
{
public:

    
    ClickVFX(TextPool* poolToUpdate, int currentSpawnLimit);
    
    void Update();

    void OnClick();

    vector<GameObject*> ActivePoolObjects;

private:
    TextPool* pool;
    int limit;
    
};
