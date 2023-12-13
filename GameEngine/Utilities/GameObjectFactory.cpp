#include "GameObjectFactory.h"

// Initialize the static member
std::vector<std::shared_ptr<GameObject>> GameObjectFactory::ActiveGameObjects;

std::shared_ptr<Image> GameObjectFactory::ConstructGameObject(Image* image)
{
    Image img = *image;
    std::shared_ptr<Image> ptr = std::make_shared<Image>(img);
    Enable(ptr);
    delete &img;
    return ptr;
}

std::shared_ptr<Text> GameObjectFactory::ConstructGameObject(Text* text)
{
    Text txt = *text;
    std::shared_ptr<Text> ptr = std::make_shared<Text>(txt);
    Enable(ptr);
    delete &txt;
    return ptr;
}

void GameObjectFactory::Enable(std::shared_ptr<GameObject> go) {
    ActiveGameObjects.push_back(go);
}

void GameObjectFactory::Disable(std::shared_ptr<GameObject> go) {
    std::erase_if(ActiveGameObjects, [go](const std::shared_ptr<GameObject>& gameObject) {
        return gameObject == go;
        });
}
