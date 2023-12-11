#include "TextPool.h"

#include "MathUtils.h"

TextPool::TextPool(Text* text, TextFactory* textFactory, int poolSize)
{
    for (int i = 0; i < poolSize; i++) {
        Text* txt = new Text(text->CurrentTransform.Position, textFactory, text->GetTextURL(), text->fontSize, text->color, text->text, text->GetRenderer());
        ObjectPool.push(txt);
        txt->Disable();
    }
    currentActiveObjects = 0;
}

GameObject* TextPool::PoolGetObject()
{
    if (ObjectPool.empty()) return nullptr;
    GameObject* frontObj = ObjectPool.front();
    ObjectPool.pop();
    currentActiveObjects += 1;
    frontObj->poolObjSpeed = MathUtils::GetRandomInt(1, 3);
    return frontObj;
}

void TextPool::PoolReturnObject(GameObject* gameObject)
{
    gameObject->Disable();
    ObjectPool.push(gameObject);
    currentActiveObjects -= 1;
}
