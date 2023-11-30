//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Text\Text.h"
#include "Utilities/Consts.h"
#include "Utilities/ImageURLs.h"
#include"Utilities/FontURLs.h"

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

	//Create Pikachu Image
	Image* pikachuImage = new Image(200, 200, IMG_PIKACHU_URL, gameWindow->renderer);

	//Create Hello Text
	Text* helloText = new Text(FONT_LAZY_URL, 100, WHITE, "hello", gameWindow->renderer);

	SDL_Event e; bool quit = false;

	//*
	//Game Loop (runs until quit)
	//*
	while (quit == false)
	{
		//Can be used, to see, how much time in ms has passed since app start
		SDL_GetTicks();

		//Loop through all pending events from Windows (OS)
		while (SDL_PollEvent(&e))
		{
			//Check, if it's an event we want to react to:
			switch (e.type) {
				case SDL_QUIT: {
					quit = true;
				} break;

				/*
				
					// This is an example on how to use input events:
				case SDL_KEYDOWN: {
					// input example: if left, then make pikachu move left
					if (e.key.keysym.sym == SDLK_LEFT) {
						pikachuMoveRight = false;
					}
					// if right, then make pikachu move right
					if (e.key.keysym.sym == SDLK_RIGHT) {
						pikachuMoveRight = true;
					}
				} break;

				*/
			} 
		}

		/*
		// This is an example for how to check, whether keys are currently pressed:
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_UP])
		{
			
		}
		if (keystate[SDL_SCANCODE_DOWN])
		{
			
		}
		*/
		gameWindow->Clear();
		
		gameWindow->Render(pikachuImage, 400, 250);
		gameWindow->Render(helloText, WINDOW_CENTER_X, 125);

		gameWindow->Present();

		//Can be used to wait for a certain amount of ms
		SDL_Delay(0);
	}

	return 0;
}