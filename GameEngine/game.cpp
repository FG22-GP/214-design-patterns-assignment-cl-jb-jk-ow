//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

#include "Text/Text.h"
#include "Utilities/Consts.h"
#include "Utilities/ImageURLs.h"
#include "Utilities/FontURLs.h"
#include "Input/InputManager.h"
#include "Utilities/Pool.h"

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

    // Create Window and Renderer
    Window* gameWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);

    // Create Pikachu Image
    Image* cubeImage = new Image(400, 400, IMG_CUBE_URL, gameWindow->renderer);
    Image* backgroundFogImage = new Image(WINDOW_WIDTH, WINDOW_HEIGHT, IMG_BACKGROUNDFOG_URL, gameWindow->renderer);

    // Create Hello Text
    Text* helloText = new Text(FONT_LAZY_URL, 100, WHITE, "hello", gameWindow->renderer);

    // Create pool
    Image* feedbackImage = new Image(100, 100, IMG_CUBE_URL, gameWindow->renderer);
    Pool* clickFeedbackPool = new Pool(128, feedbackImage);
    //GameObject* gameObject = clickFeedbackPool->PoolGetObject();
    // TODO: Add all game objects to an array so that they can be rendered.

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

        }

        // Clear the renderer
        gameWindow->Clear();

        gameWindow->Render(backgroundFogImage, 0, 0);
        gameWindow->Render(cubeImage, 50, WINDOW_CENTER_Y - 200);
        gameWindow->Render(helloText, WINDOW_CENTER_X, 125);

        gameWindow->Present();

        // Can be used to wait for a certain amount of ms
        SDL_Delay(REFRESH_RATE);
    }

    return 0;
}