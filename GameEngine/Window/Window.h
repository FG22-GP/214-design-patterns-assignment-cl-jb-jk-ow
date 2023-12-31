#pragma once
#include "../Image/Image.h"
#include "../Text/Text.h"
#include <SDL_render.h>
#include <memory>


extern class IImageLoader;

class Window
{
	//The window we'll be rendering to
	SDL_Window* window{};
	
	//The surface contained by the window
	SDL_Surface* screenSurface{};
	
	bool createdWindowSuccessfully;
	
	// Dependencies to Renderer & Image Loader
	IImageLoader* imageLoader;
public:
	Window(int width, int height, SDL_Color windowColor, const char* windowTitle);
	~Window();

	SDL_Renderer* renderer;
	
	bool WasSuccessful() { return createdWindowSuccessfully; }
	
	void Render(GameObject* gameObject);
	void Clear();
	void Present();
	std::unique_ptr<Image> LoadImage(const char* path);
};

