#include "Window.h"
#include <SDL_hints.h>

//Constructor
Window::Window(int width, int height, SDL_Color windowColor, const char* windowTitle)
{
    //Create Window and Renderer
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Make the scaled rendering look smoother.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, width, height);

    //Sets window background color
    SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
}

//Deconstructor
Window::~Window() = default;

void Window::Render(std::shared_ptr<GameObject> gameObject)
{
    SDL_RenderCopy(renderer, gameObject->Texture, nullptr, gameObject->Rect);
}

void Window::Clear()
{
    //Clear the screen
    SDL_RenderClear(renderer);
}

void Window::Present()
{
    //Present screen (switch buffers)
    SDL_RenderPresent(renderer);
}
