#include "ItemFactory.h"

#include "Consts.h"
#include "../Image/Image.h"
#include "../Text/Text.h"
#include "FontURLs.h"


Item* ItemFactory::CreateNewItem(const char* ItemName, TextFactory* textfactory, int BaseValuePerSecond, int BaseCost, int CostMultiplierPerOwnedItem, Vector2 ItemRenderPosition, const char* ItemImageURL, Shop* ItemShop, SDL_Renderer* Renderer)
{
    Image* newImage = new Image(Transform(ItemRenderPosition, Vector2(100, 100)), ItemImageURL, Renderer, WHITE);
    Text* newCostText = new Text(Vector2(100 + ItemRenderPosition.X, ItemRenderPosition.Y + 45), textfactory, FONT_FUTURAMEDIUM_URL, 15, BLACK, "COSTS:", Renderer);
    Text* newOwnedText = new Text(Vector2(100 + ItemRenderPosition.X, ItemRenderPosition.Y + 25), textfactory, FONT_FUTURAMEDIUM_URL, 15, BLACK, "OWNED:", Renderer);
    Item* newItem = new Item(ItemName, BaseValuePerSecond, BaseCost, CostMultiplierPerOwnedItem, newCostText, newOwnedText);
    Text* newNameText = new Text(Vector2(100 + ItemRenderPosition.X, ItemRenderPosition.Y), textfactory, FONT_FUTURAMEDIUM_URL, 17, BLACK, newItem->ItemName, Renderer);
    newImage->SetItemReference(newItem);
    ItemShop->AddNewShopItem(newItem);

    return newItem;
}
