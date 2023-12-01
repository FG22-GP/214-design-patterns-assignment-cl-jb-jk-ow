#pragma once
#include <SDL_rect.h>
#include <vector>

class Intersection {
public:
    static bool IntersectionMouseRect(SDL_Rect* Rect, std::vector<int> MousePos);
};
