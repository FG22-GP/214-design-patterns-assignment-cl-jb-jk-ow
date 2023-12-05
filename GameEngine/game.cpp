//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

#include "Text/Text.h"
#include "Utilities/Consts.h"
#include "Utilities/ImageURLs.h"
#include "Utilities/FontURLs.h"
#include "Input/InputManager.h"
#include "Utilities/GameObject.h"
#include "Utilities/Pool.h"
#include "Utilities/Intersection.h"
#include "Utilities/Item.h"
#include "Utilities/Shop.h"

#include "Window/Window.h"

using namespace std;

void InitializeSDL()
{
	// initialize SDL_Image for image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	// initialize SDL_ttf for font loading
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
}

Item* CreateNewItem(const char* ItemName, int BaseValuePerSecond, int BaseCost, int CostMultiplierPerOwnedItem, Vector2 ItemRenderPosition, const char* ItemImageURL, Shop* ItemShop, SDL_Renderer* Renderer)
{
    Image* previewImage = new Image(Transform(), ItemImageURL, Renderer);
    Text* nameText = new Text(Transform(Vector2(100, 0)), FONT_FUTURAMEDIUM_URL, 17, BLACK, ItemName, Renderer);
    Text* costText = new Text(Transform(Vector2(100, 45)), FONT_FUTURAMEDIUM_URL, 15, BLACK, "COSTS:", Renderer);
    Text* ownedText = new Text(Transform(Vector2(100, 25)), FONT_FUTURAMEDIUM_URL, 15, BLACK, "OWNED:", Renderer);

    Item* item = new Item(Transform(ItemRenderPosition, Vector2(100, 100)), ItemName, BaseValuePerSecond, BaseCost, CostMultiplierPerOwnedItem, previewImage, nameText, costText, ownedText);

    ItemShop->AddNewShopItem(item);

    return item;
}

int main(int argc, char* args[])
{
    InitializeSDL();

    //TODO: player stat manager thing instead?
    // Gameplay Variables
    int cubeCount = 0;
    float cpsTimer = 0;
    
    // Create Window and Renderer
    Window* gameWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);

    // Create Game Objects
    GameObject* backgroundFog = new GameObject(Transform(Vector2(0, 0), Vector2(WINDOW_WIDTH, WINDOW_HEIGHT)));
    Image* backgroundFogImage = new Image(Transform(), IMG_BACKGROUNDFOG_URL, gameWindow->sdlRenderer);
    backgroundFog->AddComponent(backgroundFogImage);

    GameObject* cube = new GameObject(Transform(Vector2(180, WINDOW_CENTER_Y - 200), Vector2(400, 400)));
    Image* cubeImage = new Image(Transform(), IMG_CUBE_URL, gameWindow->sdlRenderer);
    cube->AddComponent(cubeImage);

    GameObject* currencyCube = new GameObject(Transform(Vector2(15, 15), Vector2(70, 70)));
    Image* currencyCubeImage = new Image(Transform(), IMG_SMALLCUBE_URL, gameWindow->sdlRenderer);
    currencyCube->AddComponent(currencyCubeImage);

    GameObject* cpsCube = new GameObject(Transform(Vector2(300, 590), Vector2(45, 45)));
    Image* cpsCubeImage = new Image(Transform(), IMG_SMALLCUBE_URL, gameWindow->sdlRenderer);
    cpsCube->AddComponent(cpsCubeImage);

    GameObject* currency = new GameObject(Transform(Vector2(100, 25), Vector2(1, 1)));
    Text* currencyText = new Text(Transform(), FONT_FUTURAMEDIUM_URL, 40, WHITE, std::to_string(cubeCount).c_str(), gameWindow->sdlRenderer);
    currency->AddComponent(currencyText);

    GameObject* cps = new GameObject(Transform(Vector2(350, 595), Vector2(1, 1)));
    Text* cpsText = new Text(Transform(), FONT_FUTURAMEDIUM_URL, 30, WHITE, "512 k/cps", gameWindow->sdlRenderer);
    cps->AddComponent(cpsText);

    //Create Shop & Items
    GameObject* squareMartBackground = new GameObject(Transform(Vector2(780, -10), Vector2(250, 800)));
    Image* squareMartBackgroundImage = new Image(Transform(), IMG_SQUAREMART_URL, gameWindow->sdlRenderer);
    squareMartBackground->AddComponent(squareMartBackgroundImage);
    
    Shop* squareMart = new Shop();
    
    Item* item_SquarePants = CreateNewItem("Square Pants", 1, 10, 2, Vector2(800, 65), IMG_SQUAREPANTS_URL, squareMart, gameWindow->sdlRenderer);
    Item* item_Squire = CreateNewItem("Squire", 5, 100, 2, Vector2(800, 175), IMG_SQUIRE_URL, squareMart, gameWindow->sdlRenderer);
    Item* item_SquarePheonix = CreateNewItem("Square Pheonix", 25, 500, 3, Vector2(800, 285), IMG_SQUAREPHEONIX_URL, squareMart, gameWindow->sdlRenderer);
    Item* item_SquareSpace = CreateNewItem("Square Space", 100, 2000, 3, Vector2(800, 395), IMG_SQUARESPACE_URL, squareMart, gameWindow->sdlRenderer);
    Item* item_SquareSquared = CreateNewItem("Square Squared", 1000, 25000, 5, Vector2(800, 505), IMG_SQUARESQUARED_URL, squareMart, gameWindow->sdlRenderer);

    // Create pool
    //Image* feedbackImage = new Image(Transform(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT), Vector2(100, 100)), IMG_SQUAREPANTS_URL, gameWindow->renderer);
    //Pool* clickFeedbackPool = new Pool(128, feedbackImage);

    // Create InputManager
    InputManager inputManager;

    SDL_Event e;
    bool quit = false;

    // Game Loop (runs until quit)
    while (!quit)
    {
        // Can be used, to see, how much time in ms has passed since app start
        SDL_GetTicks();

        // Loop through all pending events from Windows (OS)
        while (SDL_PollEvent(&e))
        {
            // Check, if it's an event we want to react to:
            switch (e.type) {
                case SDL_QUIT: {
                    quit = true;
                } break;

                case SDL_KEYDOWN: {
                    // Handle key press event
                    inputManager.OnKeyPress(e.key.keysym.scancode);
                } break;

                case SDL_KEYUP: {
                    // Handle key release event
                    inputManager.OnKeyRelease(e.key.keysym.scancode);
                } break;

                case SDL_MOUSEBUTTONDOWN: {
                    // Handle mouse button down event
                   inputManager.OnMouseButtonPress(e.button.button);
                } break;

                case SDL_MOUSEBUTTONUP: {
                    // Handle mouse button down event
                    inputManager.OnMouseButtonRelease(e.button.button);
                } break;
            }
        }

        // Update input manager
        inputManager.Update();

        // Check for key presses
        if (inputManager.IsKeyPressed(SDL_SCANCODE_A)) {
            printf("'A' key is pressed\n");
        }

        // Check for mouse clicks
        if (inputManager.IsMouseButtonPressed(SDL_BUTTON_LEFT)) {
            // Handle left mouse button click at inputManager.GetMouseX(), inputManager.GetMouseY()
            printf("Left mouse button is pressed at (%d, %d)\n", inputManager.GetClickPos()[0], inputManager.GetClickPos()[1]);

            //If cube is clicked
            if(Intersection::IntersectionMouseRect(cubeImage->rect, inputManager.GetClickPos()))
            {
                cubeCount++;
            }

            //If any GameObject is clicked
            Item* ClickedItem = Intersection::GetClickedItem(GameObject::ActiveGameObjects, inputManager.GetClickPos());
            if(ClickedItem && ClickedItem != nullptr) {
                if(cubeCount >= ClickedItem->GetItemCost())
                {
                    cubeCount -= ClickedItem->GetItemCost();
                    ClickedItem->BuyItem(1);
                }
            }
        }

        currencyText->SetText(std::to_string(cubeCount).c_str());

        //Calculate CPS from items
        int currentCps = 0;

        for (auto& it: squareMart->ShopItemMap) {
            currentCps += it.second->GetItemCps();
        }

        //Add cps to cubecount every second
        if(cpsTimer >= 1000)
        {
            cpsTimer = 0;
            cubeCount += currentCps;
        }
        cpsText->SetText(std::to_string(currentCps).append("/cps").c_str());

        // Update all active game object
        for (GameObject* activeGameObject : GameObject::ActiveGameObjects)
        {
            activeGameObject->Update(REFRESH_RATE);
        }

        // Clear the renderer
        gameWindow->Clear();

        // Render all active game object renderer components
        for (GameObject* activeGameObject : GameObject::ActiveGameObjects)
        {
            for (Renderer* renderer : activeGameObject->GetRenderers())
            {
                gameWindow->Render(renderer);
            }
        }
        
        gameWindow->Present();

        cpsTimer += REFRESH_RATE;
        // Can be used to wait for a certain amount of ms
        SDL_Delay(REFRESH_RATE);
    }

    return 0;
}