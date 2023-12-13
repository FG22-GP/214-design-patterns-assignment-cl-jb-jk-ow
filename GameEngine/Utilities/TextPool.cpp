#include "TextPool.h"

#include "GameObjectFactory.h"
#include "MathUtils.h"

TextPool::TextPool(std::shared_ptr<Text> text, std::shared_ptr<TextFactory> textFactory, int poolSize)
{
    for (int i = 0; i < poolSize; i++) {
        std::shared_ptr<Text> txt(new Text(text->CurrentTransform.Position, textFactory, text->GetTextURL(), text->fontSize, text->color, text->text, text->GetRenderer()));
        ObjectPool.push(txt);
        GameObjectFactory::Disable(txt);
    }
    currentActiveObjects = 0;
}

std::shared_ptr<Text> TextPool::PoolGetObject()
{
    if (ObjectPool.empty()) return nullptr;
    std::shared_ptr<Text> frontObj = ObjectPool.front();
    ObjectPool.pop();
    currentActiveObjects += 1;
    frontObj->poolObjSpeed = MathUtils::GetRandomInt(1, 3);
    return frontObj;
}

void TextPool::PoolReturnObject(std::shared_ptr<Text> gameObject)
{
    GameObjectFactory::Disable(gameObject);
    ObjectPool.push(gameObject);
    currentActiveObjects -= 1;
}
