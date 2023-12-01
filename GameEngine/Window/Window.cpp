#include "Window.h"
#include <SDL_hints.h>

//Constructor
Window::Window(int width, int height, SDL_Color windowColor)
{
    //Create Window and Renderer
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    //Make the scaled rendering look smoother.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, width, height);

    //Sets window background color
    SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
}

//Deconstructor
Window::~Window() = default;

void Window::Render(Image* image, int x, int y)
{
    image->SetPosition(x, y);
    SDL_RenderCopy(renderer, image->imageTexture, nullptr, image->imageRect);
}

void Window::Render(Text* text, int x, int y)
{
    text->SetPosition(x, y);
    SDL_RenderCopy(renderer, text->textTexture, nullptr, text->textRect);
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
