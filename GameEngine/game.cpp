//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>

#include "Text/Text.h"
#include "Utilities/Consts.h"
#include "Utilities/ImageURLs.h"
#include "Utilities/FontURLs.h"
#include "Input/InputManager.h"
#include "Text/TextFactory.h"
#include "Utilities/Cursor.h"
#include "Utilities/GameState.h"
#include "Utilities/Pool.h"
#include "Utilities/Item.h"
#include "Utilities/SaveGameUtils.h"
#include "Utilities/Shop.h"
#include "Utilities/CubeRain.h"
#include "Utilities/ItemFactory.h"
#include "Utilities/MathUtils.h"
#include "Utilities/SDLUtils.h"
#include "Utilities/TextPool.h"
#include "VFX/ClickVFX.h"
#include "Window/Window.h"
#include "Utilities/GameObjectFactory.h"

using namespace std;

int main(int argc, char* args[])
{
    SDLUtils::InitializeSDL();
    
    // Gameplay Variables
    float cpsTimer = 0;
    //Calculate CPS from items
    int currentCps = 0;
    
    // Create Window and Renderer
    std::unique_ptr<Window> gameWindow(new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WHITE ,"CubeClicker"));

    // Create Cursor
    std::shared_ptr<SDL_Texture> cursorTexture(IMG_LoadTexture(gameWindow->renderer, IMG_CURSOR_URL));
    std::unique_ptr<Cursor> cursor(new Cursor(cursorTexture));

    std::shared_ptr<TextFactory> textFactory(new TextFactory());

    // Create Game Objects
    //std::unique_ptr<Image> backgroundFogImage(new Image(Transform(Vector2(0, 0), Vector2(WINDOW_WIDTH, WINDOW_HEIGHT)), IMG_BACKGROUNDFOG_URL, gameWindow->renderer, WHITE));

    //std::shared_ptr<GameObjectFactory> GoFactory(new GameObjectFactory);
    //std::shared_ptr<Image> BackgroungImage = GoFactory->ConstructGameObject(new Image(Transform(Vector2(0, 0), Vector2(WINDOW_WIDTH, WINDOW_HEIGHT)), IMG_BACKGROUNDFOG_URL, gameWindow->renderer, WHITE));
    
    
    //Create Pool and CubeRain asset (cuberain asset is to make use of the pool)
    // std::shared_ptr<Image> cubeRainImg(new Image(Transform(Vector2(0, WINDOW_CENTER_Y - 0), Vector2(20, 20)), IMG_CUBE_URL, gameWindow->renderer, MathUtils::GetRandomColor()));
    // GameObjectFactory::Disable(cubeRainImg);
    // std::shared_ptr<Pool> rainObjPool(new Pool(cubeRainImg, 2000, GoFactory));
    // std::unique_ptr<CubeRain> cubeRain(new CubeRain());

    std::shared_ptr<Text> clickText(new Text(Vector2(0, 0), textFactory, FONT_FUTURAMEDIUM_URL, 35, WHITE, "+1", gameWindow->renderer));
    //GameObjectFactory::Disable(clickText);
    std::shared_ptr<TextPool> clickTextPool(new TextPool(clickText, textFactory, 100));
    std::shared_ptr<ClickVFX> clickVFX(new ClickVFX(clickTextPool, 100));
    
    std::shared_ptr<Image> cubeImage(new Image(Transform(Vector2(180, WINDOW_CENTER_Y - 200), Vector2(400, 400)), IMG_CUBE_URL, gameWindow->renderer, WHITE));
    std::shared_ptr<Image> currencyCubeImage(new Image(Transform(Vector2(15, 15), Vector2(70, 70)), IMG_SMALLCUBE_URL, gameWindow->renderer, WHITE));
    std::shared_ptr<Image> cpsCubeImage(new Image(Transform(Vector2(300, 590), Vector2(45, 45)), IMG_SMALLCUBE_URL, gameWindow->renderer, WHITE));
    std::shared_ptr<Text> currencyText(new Text(Vector2(100, 25), textFactory, FONT_FUTURAMEDIUM_URL, 40, WHITE, " ", gameWindow->renderer)); //text is a space
    std::shared_ptr<Text> cpsText(new Text(Vector2(350, 595), textFactory, FONT_FUTURAMEDIUM_URL, 30, WHITE, "512 k/cps", gameWindow->renderer));
    std::shared_ptr<Text> saveText(new Text(Vector2(25, WINDOW_HEIGHT - 80), textFactory, FONT_FUTURAMEDIUM_URL, 30, WHITE, "Save Game", gameWindow->renderer));
    saveText->SetBackgroundColor(50, 50, 50, 1);
    
    //Create Shop & Items
    std::unique_ptr<Image> squareMartBackgroundImage(new Image(Transform(Vector2(780, -10), Vector2(250, 800)), IMG_SQUAREMART_URL, gameWindow->renderer, WHITE));
    std::shared_ptr<Shop> squareMart(new Shop());
    
    std::shared_ptr<Item> item_SquarePants(ItemFactory::CreateNewItem("Square Pants", textFactory, 1, 10, 2, Vector2(800, 65), IMG_SQUAREPANTS_URL, squareMart, gameWindow->renderer));
    std::shared_ptr<Item> item_Squire(ItemFactory::CreateNewItem("Squire", textFactory, 5, 100, 2, Vector2(800, 175), IMG_SQUIRE_URL, squareMart, gameWindow->renderer));
    std::shared_ptr<Item> item_SquarePhoenix(ItemFactory::CreateNewItem("Square Phoenix", textFactory, 25, 500, 3, Vector2(800, 285), IMG_SQUAREPHEONIX_URL, squareMart, gameWindow->renderer));
    std::shared_ptr<Item> item_SquareSpace(ItemFactory::CreateNewItem("Square Space", textFactory, 100, 2000, 3, Vector2(800, 395), IMG_SQUARESPACE_URL, squareMart, gameWindow->renderer));
    std::shared_ptr<Item> item_SquareSquared(ItemFactory::CreateNewItem("Square Squared", textFactory, 1000, 25000, 5, Vector2(800, 505), IMG_SQUARESQUARED_URL, squareMart, gameWindow->renderer));

    std::vector<shared_ptr<Item>> items = {item_SquarePants, item_Squire, item_SquarePhoenix, item_SquareSpace, item_SquareSquared};

    GameState gameState = SaveGameUtils::LoadGame(items);

    gameState.SetItemValuesFromSave(items);

    // Create InputManager
    InputManager inputManager(&gameState);
    inputManager.AddClickable(saveText, "save_button");
    inputManager.AddClickable(cubeImage, "cube_button");
    inputManager.AddObserver("click_vfx", clickVFX);

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

        currencyText->SetText(std::to_string(gameState.CubeCount).c_str());

        currentCps = 0;
        for (auto& it: squareMart->ShopItemMap) {
            currentCps += it.second->GetItemCps();
        }

        //Add cps to cubecount every second
        if(cpsTimer >= 1000)
        {
            cpsTimer = 0;
            gameState.CubeCount += currentCps;
        }
        cpsText->SetText(std::to_string(currentCps).append("/cps").c_str());

        // TODO: Use if to be used : Nuke if not
        // Update all active game object
        /*for (GameObject* activeGameObject : GameObject::ActiveGameObjects)
        {
            activeGameObject->Update();
        }*/

        // Clear the renderer
        gameWindow->Clear();

        // Render all active game objects
        // for (std::shared_ptr<GameObject> activeGameObject : GoFactory->ActiveGameObjects)
        // {
        //     gameWindow->Render(activeGameObject);
        // }


        //cube rain, and cuberain amt calc
       // int cubeRainLimit = static_cast<int>(std::round(static_cast<double>(currentCps) / 50.0));
        //cubeRain->Update(rainObjPool, cubeRainLimit);
        clickVFX->Update();

        cursor->UpdateCursor();
        cursor->RenderCursor(gameWindow->renderer);
        
        gameWindow->Present();

        cpsTimer += REFRESH_RATE;
        // Can be used to wait for a certain amount of ms
        SDL_Delay(REFRESH_RATE);
    }

    return 0;
}