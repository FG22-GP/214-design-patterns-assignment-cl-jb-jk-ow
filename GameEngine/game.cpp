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
#include "Utilities/Pool.h"
#include "Utilities/Intersection.h"
#include "Utilities/Item.h"

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

int main(int argc, char* args[])
{
    InitializeSDL();

    // Gameplay Variables
    int cubeCount = 0;

    //TODO: make a item creator nice thingy THIS IS TEMP
    
    // Create Window and Renderer
    Window* gameWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);

    // Create Game Objects
    //Image* backgroundFogImage = new Image(Transform(Vector2(0, 0), Vector2(WINDOW_WIDTH, WINDOW_HEIGHT)), IMG_BACKGROUNDFOG_URL, gameWindow->renderer);

    Item* TestItem = new Item("Filbert", 1, 1, 1);
    
    Image* cubeImage = new Image(Transform(Vector2(180, WINDOW_CENTER_Y - 200), Vector2(400, 400)), IMG_CUBE_URL, gameWindow->renderer);
    cubeImage->SetItemReference(TestItem);
    
    
    Image* currencyCubeImage = new Image(Transform(Vector2(15, 15), Vector2(70, 70)), IMG_SMALLCUBE_URL, gameWindow->renderer);
    Image* cpsCubeImage = new Image(Transform(Vector2(300, 590), Vector2(45, 45)), IMG_SMALLCUBE_URL, gameWindow->renderer);
    Image* squareMartBackgroundImage = new Image(Transform(Vector2(780, -10), Vector2(250, 800)), IMG_SQUAREMART_URL, gameWindow->renderer);
    Text* currencyText = new Text(Vector2(100, 25), FONT_FUTURAMEDIUM_URL, 40, WHITE, std::to_string(cubeCount).c_str(), gameWindow->renderer);
    Text* cpsText = new Text(Vector2(350, 595), FONT_FUTURAMEDIUM_URL, 30, WHITE, "512 k/cps", gameWindow->renderer);

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
        
            GameObject* ClickedItem = Intersection::GetClickedGameObject(GameObject::ActiveGameObjects, inputManager.GetClickPos());
            if(ClickedItem && ClickedItem->Item != nullptr) {
                ClickedItem->Item->BuyItem(1);
            }
        }

        currencyText->SetText(std::to_string(cubeCount).c_str());

        //TODO: properly calculate CPS
        int currentCps = cubeCount / 2;
        cpsText->SetText(std::to_string(currentCps).append("/cps").c_str());

        // Clear the renderer
        gameWindow->Clear();

        // Rendering

        for (GameObject* activeGameObject : GameObject::ActiveGameObjects)
        {
            gameWindow->Render(activeGameObject);
        }
        
        gameWindow->Present();

        // Can be used to wait for a certain amount of ms
        SDL_Delay(REFRESH_RATE);
    }

    return 0;
}