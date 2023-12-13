#pragma once
#include <memory>
#include <vector>
#include "../Image/Image.h"
#include "../Text/Text.h"

#include "GameObject.h"

class GameObjectFactory
{
public:

    GameObjectFactory() = default;

    static std::vector<std::shared_ptr<GameObject>> ActiveGameObjects;

    std::shared_ptr<Image> ConstructGameObject(Image* image);

    std::shared_ptr<Text> ConstructGameObject(Text* text);

    static void Enable(std::shared_ptr<GameObject> go);

    static void Disable(std::shared_ptr<GameObject> go);
};
