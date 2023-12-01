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

#include "Window/Window.h"

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
    Window* gameWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create Pikachu Image
    Image* pikachuImage = new Image(200, 200, IMG_PIKACHU_URL, gameWindow->renderer);

    // Create Hello Text
    Text* helloText = new Text(FONT_LAZY_URL, 100, WHITE, "hello", gameWindow->renderer);

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
                    std::vector<int> mousePosition = inputManager.OnMouseClick();
                    // Use mousePosition[0] and mousePosition[1] for X and Y coordinates
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
            printf("Left mouse button is pressed at (%d, %d)\n", inputManager.GetMouseX(), inputManager.GetMouseY());
        }

        // Clear the renderer
        gameWindow->Clear();

        gameWindow->Render(pikachuImage, 400, 250);
        gameWindow->Render(helloText, WINDOW_CENTER_X, 125);

        gameWindow->Present();

        // Can be used to wait for a certain amount of ms
        SDL_Delay(0);
    }

    return 0;
}