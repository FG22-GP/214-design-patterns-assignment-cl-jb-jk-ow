//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const char* pikachuImagePath{ "img/pikachu.png" };

int main(int argc, char* args[])
{

	//The window we'll be rendering to
	SDL_Window* window{};
	SDL_Renderer* renderer; // the window's rendering surface

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

	//Start up SDL and create window
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	// Create Window and Renderer
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
	if (!window)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	SDL_RenderSetLogicalSize(renderer, 1024, 768);

	// All data related to pikachu
	SDL_Texture* pikachu = NULL; // The final optimized image
	bool pikachuMoveRight = false;
	int pik_x, pik_y;
	pik_x = pik_y = 0;
	int pik_w, pik_h;
	pik_w = pik_h = 200;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(pikachuImagePath);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", pikachuImagePath, IMG_GetError());
		return -1;
	}
	else
	{
		//Convert surface to screen format
		pikachu = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (pikachu == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", pikachuImagePath, SDL_GetError());
			return -1;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// load font
	auto font = TTF_OpenFont("font/lazy.ttf", 100);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}

	// create text from font
	SDL_Color textColor = { 0xff, 0xff, 0xff };
	//Render text surface
	SDL_Texture* textTexture; // The final optimized image

	// render the text into an unoptimized CPU surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "The lazy fox, blah blah", textColor);
	int textWidth, textHeight;
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}
	else
	{
		// Create texture GPU-stored texture from surface pixels
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (textTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return -1;
		}
		// Get image dimensions
		auto width = textSurface->w;
		auto height = textSurface->h;
		textWidth = textSurface->w;
		textHeight = textSurface->h;
		//Get rid of old loaded surface
		SDL_FreeSurface(textSurface);
	}

	SDL_Event e; bool quit = false;

	// while the user doesn't want to quit
	while (quit == false)
	{
		SDL_GetTicks(); // can be used, to see, how much time in ms has passed since app start


		// loop through all pending events from Windows (OS)
		while (SDL_PollEvent(&e))
		{
			// check, if it's an event we want to react to:
			switch (e.type) {
				case SDL_QUIT: {
					quit = true;
				} break;

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
			} 
		}

		// This is an example for how to check, whether keys are currently pressed:
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_UP])
		{
			pik_y--;
		}
		if (keystate[SDL_SCANCODE_DOWN])
		{
			pik_y++;
		}

		// our current game logic :)
		if (pikachuMoveRight) {
			pik_x++;
			if (pik_x > 599) pikachuMoveRight = false;
		}
		else {
			pik_x--;
			if (pik_x < 1) pikachuMoveRight = true;
		}
		
		// clear the screen
		SDL_SetRenderDrawColor(renderer, 120, 60, 255, 255);
		SDL_RenderClear(renderer);
		
		// render Pikachu
		SDL_Rect targetRectangle{
			pik_x,
			pik_y,
			pik_w,
			pik_h
		};
		SDL_RenderCopy(renderer, pikachu, NULL, &targetRectangle);

		// render the text
		targetRectangle = SDL_Rect{
			500,
			500,
			textWidth,
			textHeight
		};
		SDL_RenderCopy(renderer, textTexture, NULL, &targetRectangle);

		// present screen (switch buffers)
		SDL_RenderPresent(renderer);

		SDL_Delay(0); // can be used to wait for a certain amount of ms
	}

	return 0;
}